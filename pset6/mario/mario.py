from cs50 import get_int

def print_hash(rows):
    hash_counter = 2
    space_counter = rows - 1

    for hash_char in range(rows):
        for i in range(space_counter):
            print(" ", end="")

        for j in range(hash_counter):
            print("#", end="")

        space_counter -= 1
        hash_counter += 1

        print()


def is_valid_number(number):
    if number >= 0 and number <= 23:
        return True
    return False


def make_pyramid():
    pyramid_rows = get_int("Por favor ingresa el número de columnas de la pirámide:")

    while(not is_valid_number(pyramid_rows)):
        pyramid_rows = get_int("Por favor ingresa el número de columnas de la pirámide:")

    print_hash(pyramid_rows)


def main():
    make_pyramid()


main()