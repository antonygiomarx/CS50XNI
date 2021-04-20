import sys
import cs50


''' método de cifrado, se valida si es mayúscula o minuscula, también si es alfanumerico, si no es ninguno de estos
    no se hace nada, se deja tal cual, para cifrar lo que hacemos es el carácter le restamos el número de la tabla ASCII donde empieza
    luego sumamos el key y a eso lo pasamos por mod 26 que es el tamaño del alfabeto que estamos ocupando, a eso le sumamos nuevamente
    el valor de la tabla ASCII de la letra de inicio y listo.
'''


def cipher_text(key, text):

    text = list(text)

    for i in range(len(text)):
        if text[i].islower() and text[i].isalnum():
            text[i] = ((((ord(text[i]) - ord('a')) + key) % 26) + ord('a'))

        elif text[i].isupper() and text[i].isalnum():
            text[i] = ((((ord(text[i]) - ord('A')) + key) % 26) + ord('A'))

    print(text)

    for i in range(len(text)):
        if isinstance(text[i], int):
            text[i] = chr(text[i])

    return "".join(text)


def main():
    if ((len(sys.argv) != 2) or not (int(sys.argv[1]) > 0)):
        print("Usage: ./caesar k")
        return sys.strerror(1)

    key = int(sys.argv[1])

    texto = cs50.get_string("Ingresa el texto a cifrar.\n")

    print(f"plaintext: {texto}")
    print(f"ciphertext: {cipher_text(key, texto)}")


if __name__ == '__main__':
    main()