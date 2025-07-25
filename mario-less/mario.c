#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getHeight();
void printBlock(int x);

int main(void)
{
    int height = getHeight();

    printBlock(height);
}

int getHeight()
{
    printf("The Purpose of this program is to create a Right Leaning Pyramid with #'s\n");
    int x = get_int("How tall do you want the Pyramid to be?\n");

    do
    {
        // Negative Integer + Zero

        if (x <= 0)
        {
            printf("Height must be greater then 0.\n");
            x = get_int("How tall do you want the Pyramid to be?\n");
        }
    }
    while (isalpha(x) || x <= 0);

    return x;
}

void printBlock(int x)
{
    // Rows main control
    for (int i = 1; i < x + 1; i++)
    {

        // Chars in each row, spaces
        for (int j = x; j > i; j--)
        {
            printf(" ");
        }
        // Stars in each row
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
