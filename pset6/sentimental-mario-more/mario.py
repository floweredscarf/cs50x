from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

for row in range(height):
    print(" " * (height - row - 1), end="")
    print("#" * (row + 1), end="")
    print(" " * 2, end="")
    print("#" * (row + 1))