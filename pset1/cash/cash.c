#include <cs50.h>
#include <stdio.h>

int calculate_coins(int cents, int value);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_coins(cents, 25);

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = calculate_coins(cents, 10);

    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickels = calculate_coins(cents, 5);

    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickels * 5);

    // Calculate how many pennies you should give customer
    int pennies = calculate_coins(cents, 1);

    // Subtract the value of those pennies from remaining cents
    cents = cents - (pennies * 1);

    // Sum the number of quarters, dimes, nickels, and pennies used
    int sum = quarters + dimes + nickels + pennies;
    // Print that sum
    printf("%i\n", sum);
}

int calculate_coins(int cents, int value)
{
    // Calculate how many quarters you should give customer
    int coins = 0;
    while (cents >= value)
    {
        coins++;
        cents = cents - value;
    }
    return coins;
}