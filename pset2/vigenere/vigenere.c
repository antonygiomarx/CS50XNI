#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include<cs50.h>
#include<string.h>

/*
*@author antonygiomarx
*@description cifrado Vigenere en C
*/

void cipher_text(string key, string text);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");

        return 1;
    }

    string key = argv[1];

    for (int i = 0; i < strlen(key); i++)
    {
        if (!(isalpha(key[i])))
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }


    string texto = get_string("Ingresa el texto a cifrar.\n");

    printf("plaintext: %s\n", texto);
    cipher_text(key, texto);
    printf("ciphertext: %s\n", texto);
}

/* método de cifrado, se valida si es mayúscula o minuscula, si no es ninguno de estos
 * no se hace nada, se deja tal cual, para cifrar lo que hacemos es el carácter le restamos el número de la tabla ASCII donde empieza
 * luego sumamos el una variable que la sacamos haciendo cada caracter del key en minuscula, luego a la variable k del contador le sacamos el residuo de
 * la longitud del key y a eso lo pasamos por mod 26 que es el tamaño del alfabeto que estamos ocupando, a eso le sumamos nuevamente
 * el valor de la tabla ASCII de la letra de inicio y listo.
 */
void cipher_text(string key, char text[])
{
    int letter_key;

    for (int i = 0, k = 0; i < strlen(text); i++)
    {
        letter_key = tolower(key[k % strlen(key)]) - 'a';

        if (islower(text[i]))
        {
            text[i] = (((text[i] - 'a' + letter_key) % 26) + 'a');
            k++;
        }
        else if (isupper(text[i]))
        {
            text[i] = (((text[i] - 'A' + letter_key) % 26) + 'A');
            k++;
        }
    }
}