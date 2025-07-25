#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

string getCard();
int checkVal(string array);

int main (void)
{
    string card = getCard();
    checkVal(card);
}

string getCard()
{
    string x = get_string("Please enter the card number: \n");
    bool num = true;

    // check if it is all numbers
    do
    {
        for(int i=0; i < strlen(x); i++)
        {
            num = true;
            if(x[i] < 48 || x[i] > 57)
            {
                x = get_string("Enter a valid numerical card number: \n");
                num = false;
            }
        }
    } while (!num);
    return x;
}

int checkVal(string array)
{
    // MAIN DECLARATIONS
    int i = 0;
    int j = 0;
    int k = 0;
    int l = strlen(array)-1;


    // MATH
        // ISOLATE ALT DIGITS FROM END, MULITPLY BY 2 (SEPERATE INTO INDIVIDUAL DGITS IF > 10), AND ADD THEM ALL {DO WHILE USKE ANDAR IF ELSE}
    for(i=l; i >= 0; i--)
    {

    }


        // RETURN FROM THE + ABOVE NOT ALT DIGITS WHICH WERE NOT MULTIPLIED BY 2

        // DIVIDE THIS NUMBER BY 10. IF REMAINDER IS 0, CHECK 3,4 OR 5 START AND PRINT. ELSE INVALID

    printf("%i\n", l);
    return l;
}
