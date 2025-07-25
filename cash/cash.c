#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getChange();
int countCoins(int x);

int main(void)
{
    int change = getChange();
    int final = countCoins(change);
    printf("%i\n", final);
}

// Rejects negative and 0
int getChange()
{
    int x = 0;
    while (x < 1)
    {
        printf("Change to be dispensed should be more than 0. \n");
        x = get_int("Change owed: ");
    }
    return x;
}

// 25,10,5,1 cents for change
int countCoins(int x)
{
    int change = x;
    int pachhis = 0;
    int dus = 0;
    int panch = 0;
    int ek = 0;
    int chutte = 0;

    while (change >= 25)
    {
        pachhis = change / 25;

        change = change - (pachhis * 25);
    }

    while (change >= 10)
    {
        dus = change / 10;

        change = change - (dus * 10);
    }

    while (change >= 5)
    {
        panch = change / 5;

        change = change - (panch * 5);
    }

    while (change >= 1)
    {
        ek = change;
        change = 0;
    }
    chutte = pachhis + dus + panch + ek;
    return chutte;
}
