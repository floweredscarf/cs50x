#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    int checksum = 0;
    int count = 0;
    int start_two = 0;
    int start_one = 0;
    while (number > 0)
    {
        if (number < 100 && number > 10)
        {
            start_two = number;
        }
        if (number < 10)
        {
            start_one = number;
        }
        // Luhn's Algorithm
        if (count % 2 == 1)
        {
            checksum += (number % 10 * 2) % 10 + (number % 10 * 2) / 10;
        }
        else
        {
            checksum += number % 10;
        }
        number /= 10;
        count++;
    }

    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
    }

    // American Express
    else if (count == 15 && (start_two == 34 || start_two == 37))
    {
        printf("AMEX\n");
    }

    // MasterCard
    else if (count == 16 && (start_two == 51 || start_two == 52 || start_two == 53 ||
                             start_two == 54 || start_two == 55))
    {
        printf("MASTERCARD\n");
    }

    // Visa
    else if (count == 13 && start_one == 4)
    {
        printf("VISA\n");
    }
    else if (count == 16 && start_one == 4)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
