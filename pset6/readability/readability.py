from cs50 import get_string


def main():
    # prompt user for input
    grade = get_string("Text: ")

    # storing value of string length
    length = len(grade)

    # calling letters function
    l = letters(length, grade)

    # calling words function
    w = words(length, grade)

    # calling sentences function
    s = sentences(length, grade)

    # calculator for the grade of text
    L = l / w * 100
    S = s / w * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    x = round(index)

    # printing the grade of the text
    if x >= 1 and x <= 16:
        print(f"Grade {x}")
    elif x < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")

# defining function for counting letters


def letters(a, b):
    c = 0
    for q in range(a):
        if (b[q] >= 'a' and b[q] <= 'z') or (b[q] >= 'A' and b[q] <= 'Z'):
            c += 1
    return c

# defining function for counting words


def words(a, b):
    c = 1
    for q in range(a):
        if (b[q] == ' '):
            c += 1
    return c

# defining function for counting sentences


def sentences(a, b):
    c = 0
    for q in range(a):
        if (b[q] == '.' or b[q] == '?' or b[q] == '!'):
            c += 1
    return c


main()