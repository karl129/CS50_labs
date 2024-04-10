# TODO

def main():
    card_id = input("Number: ")

    first2 = int(card_id[:2])
    length = len(card_id)
    # visa
    if (first2 >= 40 and first2 <= 49) and (length == 13 or length == 16):
        checksum = get_check(card_id, length)
        if checksum_valid(checksum):
            print("VISA")
        else:
            print("INVALID")

    # amex
    elif (first2 == 34 or first2 == 37) and (length == 15):
        checksum = get_check(card_id, length)
        if checksum_valid(checksum):
            print("AMEX")
        else:
            print("INVALID")

    # mastercard
    elif 51 <= first2 <= 55 and length == 16:
        checksum = get_check(card_id, length)
        if checksum_valid(checksum):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def get_check(card_id, length):
    s_sum = d_sum = 0
    for i in range(length):
        if i % 2 != 0:
            d_last = int(card_id[-1 - i]) * 2
            d_sum += d_last // 10 + d_last % 10
        else:
            s_sum += int(card_id[-1 - i])
    return s_sum + d_sum


def checksum_valid(checksum):
    if not (checksum % 10):
        return True
    else:
        return False


main()
