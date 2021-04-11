#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>



void validate_card_emisor(string card_number);
string get_credit_card();
bool validate_input(string input_credit_card);
bool validate_card(string card_number);
bool calculate_card(string card_number);


int main(void)
{
    string credit_card = get_credit_card();
    bool is_valid_card = validate_input(credit_card);

    if (!is_valid_card)
    {
        credit_card = get_credit_card();
        is_valid_card = validate_input(credit_card);

        while (!is_valid_card)
        {
            credit_card = get_credit_card();
            is_valid_card = validate_input(credit_card);
        }
    }

    validate_card_emisor(credit_card);

    return 0;
}

string get_credit_card()
{
    string input_credit_card = get_string("Ingresa tu tarjeta de crédito: \n");
    return input_credit_card;
}

void validate_card_emisor(string card_number)
{
    if (!validate_card(card_number))
    {
        printf("INVALID\n");
    }
    else
    {
        if ((card_number[0] == '3') && (card_number[1] == '7' || card_number[1] == '4'))
        {
            if (validate_card(card_number))
            {
                printf("AMEX\n");
            }
        }
        else if (card_number[0] == '4')
        {
            if (validate_card(card_number))
            {
                printf("VISA\n");
            }
        }
        else if ((card_number[0] == '5') && (card_number[1] == '1' || card_number[1] == '2' || card_number[1] == '3'
                                             || card_number[1] == '4' || card_number[1] == '5'))
        {
            if (validate_card(card_number))
            {
                printf("MASTERCARD\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

bool validate_card(string card_number)
{
    if (calculate_card(card_number))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool calculate_card(string card_number)
{
    int acc = 0;

    for (int i = 1; i <= strlen(card_number); i += 2)
    {
        int i_number = ((int)card_number[i] - 48) * 2;

        if (i_number > 9)
        {
            acc += i_number - 9;
        }
        else
        {
            acc += i_number;
        }


    }

    for (int i = 0; i <= strlen(card_number); i += 2)
    {
        int i_number = ((int)card_number[i] - 48);
        acc += i_number;
    }


    acc = (acc % 10);


    if (acc % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validate_input(string input_credit_card)
{
    regex_t regex;

    int validate_credit_card_regex = regcomp(&regex, "^[0-9]*$", 0);
    int validate_credit_card_regex_exec = regexec(&regex, input_credit_card, 0, NULL, 0);

    if (validate_credit_card_regex == 0 && validate_credit_card_regex_exec == 0)
    {
        return true;
    }
    else
    {
        return false;
    }


}