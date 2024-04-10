# TODO

def main():
    text = input("Text: ")
    counters = counter(text)
    grade = readability_checker(counters)
    print_grade(grade)


def counter(text):
    alpha_count = sum(1 for char in text if char.isalpha())
    space_count = text.count(' ') + 1
    punctuation_count = sum(1 for char in text if char in '.?!')

    return [alpha_count, space_count, punctuation_count]


def readability_checker(counter):
    l = counter[0] / counter[1] * 100
    s = counter[2] / counter[1] * 100

    return round(0.0588 * l - 0.296 * s - 15.8)


def print_grade(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


main()
