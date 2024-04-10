import re


def main():
    cents = int(get_cents("Change owed: ") * 100)

    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    pennies = calculate_pennies(cents)

    coins = quarters + dimes + nickels + pennies

    print(coins)


def get_cents(prompt):
    while True:
        s = input(prompt)
        if s is None:
            continue
        if len(s) > 0 and re.search(r"^[+-]?\d*(?:\.\d*)?$", s):
            try:
                if float(s) > 0:
                    return float(s)
            except (OverflowError, ValueError):
                pass


def calculate_quarters(cents):
    return cents // 25


def calculate_dimes(cents):
    return cents // 10


def calculate_nickels(cents):
    return cents // 5


def calculate_pennies(cents):
    return cents


main()
