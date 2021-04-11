from cs50 import get_float

def greedy (number):
    quarter = 0
    dime = 0
    nickel = 0
    cent = 0

    while ((number - 25) >= 0):
        quarter += 1
        number = number - 25

    while ((number - 10) >= 0):
        dime += 1
        number = number - 10

    while ((number - 5) >= 0):
        nickel += 1
        number = number - 5

    while ((number - 1) >= 0):
        cent += 1
        number = number -1

    return (quarter + dime + nickel + cent)

def main():
    input_number = get_float("Ingresa un número: ")

    while (input_number < 0):
        input_number = get_float("Ingresa un número: ")

    number = input_number * 100

    print(greedy(int(number)))


main()