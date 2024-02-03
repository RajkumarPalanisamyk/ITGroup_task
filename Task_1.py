
from typing import List


def average_calc():
    total_sum = 0.0
    count = 0

    while True:
        try:
            user_input = input("Enter a number (or 'x' to exit): ")

            if user_input.lower() == 'x':
                break

            value = float(user_input)
            count += 1
            total_sum += value
            average = total_sum / count
            print("Current Average:", average)

        except ValueError:
            print("Invalid input. Please enter a numeric value or 'x' to exit.")

    print("Program terminated.")


if __name__ == '__main__':
    average_calc()