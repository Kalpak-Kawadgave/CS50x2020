from sys import argv, exit
import csv
from cs50 import SQL

# check for the aommand line arguments
if len(argv) != 2:
    print("Usage: python import.py housename")
    exit(1)
# store input house from user
house = argv[1]

# link sql and python
db = SQL("sqlite:///students.db")

# get dict sorted according to the requirements
p = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last,first", house)
for row in p:
    # check if middle name exists and print output accordingly
    if row['middle'] == None:
        print("{0} {1}, born {2}".format(row['first'], row['last'], row['birth']))
    else:
        print("{0} {1} {2}, born {3}".format(row['first'], row['middle'], row['last'], row['birth']))