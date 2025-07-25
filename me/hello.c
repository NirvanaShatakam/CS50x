#include <cs50.h>
#include <stdio.h>

string getname();
void printname(string x);

int main(void)
{
    string name = getname();
    printname(name);
}

string getname()
{
    string x = get_string("Please enter your name: \n");
    return x;
}

void printname(string x)
{
    printf("hello, %s\n", x);
}
