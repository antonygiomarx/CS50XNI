#include <stdio.h>
#include <cs50.h>
#include <math.h>


int greedy(int number)
{
    int quarter = 0;
    int dime = 0;
    int nickel = 0;
    int cent = 0;

    while((number - 25) >= 0)
    {
        quarter++;
        number = number - 25;
    }

    while((number - 10) >= 0)
    {
        dime++;
        number = number - 10;
    }

    while((number - 5) >= 0)
    {
        nickel++;
        number = number - 5;
    }

    while((number - 1) >= 0)
    {
        cent++;
        number = number - 1;
    }

    return (quarter + dime + nickel + cent);
}

int main (void)
{

    float input_number = get_float("Ingresa un número: \n");

    while(input_number < 0)
    {
        input_number = get_float("Ingresa un número: \n");
    }

    /*
    La razón por la que se agrega 0.5 al castear a entero es debido a la inexactitud en punto flotante.
    En algunos casos se agrega más o menos dependiendo del caso y esto afecta al resultado final, por ende al agregar el 0.5 se evita esto.
    */
    int number = input_number * 100 + 0.5;

    int greedy_number = greedy(number);

    printf("%d\n", greedy_number);

    return 0;
}