from cs50 import get_int

# Prompt user to input height
height = get_int("Height: ")
while (height <= 0 or height >= 9):
    height = get_int("Height: ")
# Print stairs
for i in range(height):
    for j in range(height):
        if j >= height - i - 1:
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    for j in range(height):
        if j <= i:
            print("#", end="")
    print()

