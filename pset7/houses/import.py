from sys import argv, exit
import csv
from cs50 import SQL

# check for the aommand line arguments
if len(argv) != 2:
    print("Usage: python import.py filename.csv")
    exit(1)

# link sql and python
db = SQL("sqlite:///students.db")

# open the input file
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # split the name to first middle and last
        name = row['name']
        new = name.split()
        if len(new) == 2:
            new.insert(1, None)
        # insert the values in the database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   new[0], new[1], new[2], row['house'], row['birth'])