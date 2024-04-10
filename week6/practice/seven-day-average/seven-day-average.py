import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)
    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_case = {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])
        if state not in new_cases:
            new_cases[state] = []
        if len(new_cases[state]) >= 14:
            new_cases[state].pop(0)
        if state not in previous_case:
            previous_case[state] = 0
        daily_case = cases - previous_case[state]
        previous_case[state] = cases
        new_cases[state].append(daily_case)

    return new_cases

# TODO: Calculate and print out seven day average for given state


def comparative_averages(new_cases, states):
    for state in states:
        recent_week = sum(new_cases[state][-7:]) / 7
        previous_week = sum(new_cases[state][:7]) / 7

        try:
            incrs_pct = (recent_week - previous_week) / previous_week * 100
        except ZeroDivisionError:
            incrs_pct = 0

        if incrs_pct < 0:
            trend = "decrease"
        else:
            trend = "increase"

        print(f"{state} had a 7-day average of {recent_week:.0f} and a {trend} of {abs(incrs_pct):.0f}%")


main()
