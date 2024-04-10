menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}


costs = 0
while True:
    try:
        item = input("Item: ").title()
        if item in menu:
            costs += menu[item]
            print(f"Total: ${costs:.2f}")
    except EOFError:
        break
