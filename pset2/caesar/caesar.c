#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include<cs50.h>
#include<string.h>

/*
*@author antonygiomarx
*@description cifrado César en C
*/

void cipher_text(int key, string text);

int main(int argc, string argv[])
{

    if (argc != 2 || !(atoi(argv[1]) > 0))
    {
        printf("Usage: ./caesar k\n");

        return 1;
    }

    int key = atoi(argv[1]);


    string texto = get_string("Ingresa el texto a cifrar.\n");

    printf("plaintext: %s\n", texto);
    cipher_text(key, texto);
    printf("ciphertext: %s\n", texto);
}

/* método de cifrado, se valida si es mayúscula o minuscula, también si es alfanumerico, si no es ninguno de estos
 * no se hace nada, se deja tal cual, para cifrar lo que hacemos es el carácter le restamos el número de la tabla ASCII donde empieza
 * luego sumamos el key y a eso lo pasamos por mod 26 que es el tamaño del alfabeto que estamos ocupando, a eso le sumamos nuevamente
 * el valor de la tabla ASCII de la letra de inicio y listo.
 */
void cipher_text(int key, char text[])
{

    for (int i = 0; i < strlen(text); i++)
    {

        if (islower(text[i]) && isalpha(text[i]))
        {
            text[i] = ((((text[i] - 'a') + key) % 26) + 'a');
        }
        else if (isupper(text[i]) && isalpha(text[i]))
        {
            text[i] = ((((text[i] - 'A') + key) % 26) + 'A');
        }
    }
}