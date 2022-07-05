from cs50 import get_int, get_string
from sys import exit

# sum
sum = 0

# checker
def check(a, b):
    # globalising sum
    global sum
    # iterating over the number
    for i in range(b):
        # sum for numbers at even places
        if i % 2 == 0:
            c = a % 10
            a = a // 10
            sum = sum + c
        # sum for numbers at odd places
        else:
            c = (a % 10) * 2
            a = a // 10
            # workaround for double digit sums
            if c > 9:
                c = (c % 10) + (c // 10)
            sum = sum + c
    # check for valid number
    if sum % 10 == 0:
        return True
    else:
        return False


# get input from user
input = get_int("Number: ")
l = len(str(input))

# check for type of card
if l != 13 and l != 15 and l != 16:
    print("INVALID")
    exit()
if check(input, l) == True:
    if l == 13:
        if input // 1e12 == 4:
            print("VISA")
            exit()
    elif l == 15:
        if input // 1e13 == 34 or input // 1e13 == 37:
            print("AMEX")
            exit()
    elif l == 16:
        if input // 1e14 == 51 or input // 1e14 == 52 or input // 1e14 == 53 or input // 1e14 == 54 or input // 1e14 == 55:
            print("MASTERCARD")
            exit()
        if input // 1e15 == 4:
            print("VISA")
            exit()
    else:
        print("INVALID")
        exit()
else:
    print("INVALID")
    exit()