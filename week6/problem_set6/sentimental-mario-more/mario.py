while True:
    try:
        height = int(input("Enter a height between 1 and 8: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        pass

for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
