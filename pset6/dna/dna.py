import csv
from sys import argv, exit

# check for the command line arguments
if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

l = [0]
counter = 0
temp = 0
# load the csv file in memory
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    # store the headers in for the STR
    headers = reader.fieldnames
    for i in range(1, len(headers)):
        # open the test file
        with open(argv[2], "r") as seq:
            test = seq.read()
            for j in range(len(test)):
                while True:
                    if test[j:j + len(headers[i])] == headers[i]:
                        counter += 1
                        j = j + len(headers[i])
                    else:
                        if temp < counter:
                            temp = counter
                        counter = 0
                        break
            # append th STR counts
            l.append(temp)
            temp = 0
with open(argv[1], "r") as file:
    reader = csv.reader(file)
    # begin the check
    for row in reader:
        flag = 1
        if temp == 0:
            temp = 1
            continue
        for i in range(1, len(row)):
            if(int(row[i]) != l[i]):
                flag = 0
                break
        if flag == 1:
            print(row[0])
            exit(0)
print("No match")