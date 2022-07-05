import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
db.execute("CREATE TABLE IF NOT EXISTS 'users' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'username' TEXT NOT NULL, 'hash' TEXT NOT NULL, 'cash' NUMERIC NOT NULL DEFAULT 10000.00 )")
db.execute("CREATE TABLE IF NOT EXISTS 'history' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL , 'user_id' NUMERIC NOT NULL, 'company_id' NUMERIC NOT NULL, 'shares' NUMERIC NOT NULL, 'price' NUMERIC NOT NULL, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)")
db.execute("CREATE TABLE IF NOT EXISTS 'companies' ('company_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'symbol' TEXT NOT NULL, 'name' TEXT NOT NULL, 'price' NUMERIC NOT NULL, 'total' NUMERIC)")

def price_updater():
    companies = db.execute("SELECT symbol FROM companies")
    for company in companies:
        symbol = company['symbol']
        look = lookup(symbol)
        price = look['price']
        db.execute("UPDATE companies SET price = :price WHERE symbol = :symbol", price = price, symbol = symbol)

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    uid = session["user_id"]
    price_updater()
    index = db.execute("SELECT * FROM (SELECT * FROM (SELECT company_id AS a, SUM (shares) AS b, price FROM history WHERE user_id = :uid GROUP BY company_id) JOIN companies ON a = companies.company_id ORDER BY symbol) WHERE b > 0", uid = uid)
    data = (db.execute("SELECT * FROM users WHERE id = :uid", uid=uid))
    cash = usd(data[0]['cash'])
    final_amt = float(data[0]['cash'])
    for i in index:
        i['total'] = i['b'] * i['price']
        final_amt = final_amt + i['total']
        i['total'] = usd(i['total'])
    final_amt = usd(final_amt)
    return render_template("index.html",index=index, cash = cash, final_amt = final_amt)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Ensure symbol exists
        symbol = request.form.get("Symbol")
        look = lookup(symbol)
        if (look == None):
            return apology("invalid symbol", 400)

        # Get the details for record and validation
        uid = session["user_id"]
        data = (db.execute("SELECT * FROM users WHERE id = :uid", uid=uid))
        cash = data[0]['cash']
        shares = float(request.form.get("Shares"))
        price = float(look['price'])
        name = look['name']
        company_id = 0
        remain = cash - (price * shares)

        # Check for available cash
        if (price * shares > cash):
            return apology("can't afford", 400)

        # Update tables and redirect
        flash("Bought!")
        db.execute("UPDATE users SET cash = :a WHERE id = :uid", a = remain, uid=uid)
        company_table = db.execute("SELECT company_id FROM companies WHERE symbol = :symbol", symbol=symbol)
        if len(company_table) == 0:
            db.execute("INSERT INTO companies (symbol, name, price) VALUES(?, ?, ?)", symbol , name, price)
            company_table = db.execute("SELECT company_id FROM companies WHERE symbol = :symbol", symbol=symbol)
            company_id = company_table[0]['company_id']
        else:
            company_id = company_table[0]['company_id']
        db.execute("INSERT INTO history (user_id, company_id, shares, price) VALUES(?, ?, ?, ?)", uid, company_id, shares, price)
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html", flag = 0)


@app.route("/history")
@login_required
def history():
    uid = session["user_id"]
    index = db.execute("SELECT * FROM (SELECT company_id AS a, shares, price, created_at FROM history WHERE user_id = :uid) JOIN companies ON a= companies.company_id ORDER BY created_at",uid = uid)
    return render_template("history.html", index = index)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        # Ensure username was submitted
        symbol = request.form.get("Symbol")
        look = lookup(symbol)
        print(look)
        if (look == None):
            return apology("invalid symbol", 400)
        name = look['name']
        symbol = look['symbol']
        price = look['price']
        return render_template("quote.html",name = name, symbol =symbol, price =price, flag = 1)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html", flag = 0)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 0:
            flash("Username is not available")
            return redirect("/register")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # Insert username and password in the database
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
        data = db.execute("SELECT * FROM users WHERE username =:username ", username = username)
        # Remember which user has logged in
        session["user_id"] = data[0]['id']

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    uid = session["user_id"]
    if request.method == "POST":
        # Ensure symbol exists
        symbol = request.form.get("symbol")
        print(symbol)
        if(symbol == None):
            return apology("missing symbol", 400)
        look = lookup(symbol)
        price = float(look['price'])
        shares = float(request.form.get("shares"))
        index = db.execute("SELECT * FROM (SELECT * FROM (SELECT company_id AS a, SUM (shares) AS b, price FROM history WHERE user_id = :uid GROUP BY company_id) JOIN companies ON a = companies.company_id ORDER BY symbol) WHERE b > 0", uid = uid)
        if (shares > index[0]['b'] ):
            return apology("too many shares", 400)
        # Get the details for record and validation
        uid = session["user_id"]
        flash("Sold!")
        data = (db.execute("SELECT * FROM users WHERE id = :uid", uid=uid))
        cash = data[0]['cash']
        a = cash + price * shares
        shares = - shares
        # Update tables and redirect
        db.execute("UPDATE users SET cash = :a WHERE id = :uid", a = a, uid=uid)
        company_table = db.execute("SELECT company_id FROM companies WHERE symbol = :symbol", symbol=symbol)
        company_id = company_table[0]['company_id']
        db.execute("INSERT INTO history (user_id, company_id, shares, price) VALUES(?, ?, ?, ?)", uid, company_id, shares, price)
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        index = db.execute("SELECT * FROM (SELECT * FROM (SELECT company_id AS a, SUM (shares) AS b, price FROM history WHERE user_id = :uid GROUP BY company_id) JOIN companies ON a = companies.company_id ORDER BY symbol) WHERE b > 0", uid = uid)
        return render_template("sell.html", index = index)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)