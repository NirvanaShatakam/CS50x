#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions Needed
// assign value, sort and compile

int assValue(char x);
int sortCompile(string x);
string lower(string x);

int main(void)
{
    // Get words
    string x = get_string("Player 1: \n");
    string y = get_string("Player 2: \n");

    x = lower(x);
    y = lower(y);

    int valx = sortCompile(x);
    int valy = sortCompile(y);

    if (valx == valy)
    {
        printf("Tie!\n");
    }
    else if (valx > valy)
    {
        printf("Player 1 wins!\n");
    }
    else if (valx < valy)
    {
        printf("Player 2 wins!\n");
    }
}

int sortCompile(string x)
{
    int points = 0;
    int len = strlen(x);
    int val = 0;
    // sort letters and assign values accordingly
    for (int i = 0; i < len; i++)
    {
        char a = x[i];
        points = assValue(a);
        val = val + points;
    }

    return val;
}

int assValue(char x)
{
    int temp = 0;
    // A,E,I,L,N,O,R,S,T,U - 1 Points
    // D,G
    // B,C,M,P
    // F,H,v,w,Y
    // K
    // J,X - 8 Points
    // Q,Z - 10 Points

    if (x == 'a' || x == 'e' || x == 'i' || x == 'l' || x == 'n' || x == 'o' || x == 'r' ||
        x == 's' || x == 't' || x == 'u')
    {
        temp = 1;
    }
    else if (x == 'd' || x == 'g')
    {
        temp = 2;
    }
    else if (x == 'b' || x == 'c' || x == 'm' || x == 'p')
    {
        temp = 3;
    }
    else if (x == 'f' || x == 'h' || x == 'v' || x == 'w' || x == 'y')
    {
        temp = 4;
    }
    else if (x == 'k')
    {
        temp = 5;
    }
    else if (x == 'j' || x == 'x')
    {
        temp = 8;
    }
    else if (x == 'q' || x == 'z')
    {
        temp = 10;
    }

    return temp;
}

string lower(string x)
{
    int len = strlen(x);
    for (int i = 0; i < len; i++)
    {
        if (x[i] < 91)
        {
            x[i] = x[i] + ('a' - 'A');
        }
    }
    return x;
}

// for loop for sorting through each character
// if conditional to indentify and assign value
//  add with each iteration or return value after each iteration and add(x = x + return)
