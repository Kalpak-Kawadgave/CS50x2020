from cs50 import get_int

height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")
a = 1
b = height - 1
for i in range(height):
    print(" " * b + "#" * a + "  " + "#" * a)
    a += 1
    b -= 1