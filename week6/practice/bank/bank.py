greeting = input("Greeting: ").lower()

if "hello" in greeting:
    print("$0")
elif greeting.startswith('h'):
    print("$20")
else:
    print("$100")
