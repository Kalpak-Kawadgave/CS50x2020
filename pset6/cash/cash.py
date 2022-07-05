from cs50 import get_float

input = -1
while input < 0:
    input = get_float("Change owed: ")
input *= 100
a = input // 25
input = input - a * 25

b = input // 10
input = input - b * 10

c = input // 5
input = input - c * 5

d = input // 1

print(int(a + b + c + d))