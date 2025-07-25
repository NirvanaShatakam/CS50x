# Similar as mario-more

# take input for height
height = (input("Height: "))


# check if height is an integer and between one and eight
while not height.isdigit():
    height = (input("Enter a valid height between 1 and 8.\nHeight: "))
if height.isdigit():
    h = int(height)
    while not (1 <= h <= 8):
        h = int(input("Enter a valid height between 1 and 8.\nHeight: "))


# now we start the loop
for i in range(h):
    for _ in range(h - i - 1):
        print(" ", end="")
    for _ in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for _ in range(i + 1):
        print("#", end="")
    print()
