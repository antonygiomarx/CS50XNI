#include <stdio.h>
#include <cs50.h>


void print_hash(int rows)
{
    // Valor por defecto de los hashes será 2.
    int hash_counter = 2;

    // Es el espacio que va a tomar de izquiera a derecha.
    int space_counter = rows - 1;

    char hash[] = "#";

    // Iteramos las filas conforme a lo que ingresa el usuario.
    for (int i = 0; i < rows; i++)
    {
        // Agregamos los espacio de izquierda a derecha.
        for (int j = 0; j < space_counter; j++)
        {
            printf(" ");
        }
        // Imprimimos los hashes correspondientes a la fila.
        for (int k = 0; k < hash_counter; k++)
        {
            printf("%s", hash);
        }

        // Reducimos el espacio de la izquierda para que vaya tomando forma.
        space_counter--;

        // Aumentamos los hashes a imprimir en cada iteración.
        hash_counter++;

        // Hacemos un salto de línea al final de cada iteración de las filas.
        printf("\n");

    }
}
/*
Validamos si el número es válido y retornamos true o false
en caso que se cumpla la condición.
*/
bool is_valid_number(int number)
{
    if (number >= 0 && number <= 23)
    {
        return true;
    }
    return false;
}

// Función principal, se va a encargar de solicitar los datos y mandar a llamar la impresión.
void make_pyramid()
{
    int pyramid_rows = get_int("Por favor ingresa el número de columnas de las pirámide: \n");

    // Si el número no es válido se solicita nuevamente hasta que lo sea.
    while (!is_valid_number(pyramid_rows))
    {
        pyramid_rows = get_int("Por favor ingresa el número de columnas de las pirámide: \n");
    }

    // Se manda a imprimir la pirámide.
    print_hash(pyramid_rows);
}

int main(void)
{
    make_pyramid();
    return 0;
}