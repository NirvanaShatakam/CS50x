#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// take in input from command line [argc,argv]
// you need to find the no. of sentences per 100 words and no of letters per 100 words
    // set up counters and iterate trough every character in the input string
    // every space = word++ & every '.,?,!' = sentence++
    // return (make seperate functions to count words and sentences. or find out if a single function can return two variables)
// Math the Math
// Configure the output


//Functions Needed
//countSentence(. ! ?), countWords(already there argc-1), findScore

bool countSentence (string x);
float countScore (float x, float y);
int countLetters (string x);
int countWords (string x);

int main (int argc, string argv[])
{
    int words = 0;
    int sentences = 0;
    int letters = 0;
    int spaces = 0;

    for(int i = 1, len = argc - 1; i <= len; i++)
    {
        bool ans = countSentence (argv[i]);
        if(ans == true)
        {
            sentences++;
        }
    }

    for(int i = 1, len = argc - 1; i <= len; i++)
    {
        int ans = countLetters (argv[i]);
        letters = letters + ans;
    }

    for(int i = 1, len = argc - 1; i <= len; i++)
    {
        int ans = countWords (argv[i]);
        spaces = spaces + ans;
    }

    words = spaces + (argc -1);


    float l = ((float)letters/(float)words)*100;
    float k = ((float)sentences/(float)words)*100;

    float score = countScore(l,k);

    int level = round(score);

    //printf("%i\n", letters);
    //printf("%i\n", argc-1);
    //printf("%i\n", sentences);
    //printf("%f\n", score);
    //printf("%i\n", level);

    if(score <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if(score >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }

}


bool countSentence (string x)
{
    bool sent = false;

    for(int i = 0, len = strlen(x); i < len; i++)
    {
        char temp = x[i];
        if(temp == '.' || temp == '?' || temp == '!')
        {
            sent = true;
            return sent;
        }
    }
    return sent;
}

int countLetters (string x)
{
    int letters = 0;

    for(int i = 0, len = strlen(x); i < len; i++)
    {
        if(isalpha(x[i]))
        {
            letters++;
        }
    }
    return letters;
}

int countWords (string x)
{
    int spaces = 0;

    for(int i = 0, len = strlen(x); i < len; i++)
    {
        if(x[i] == ' ')
        {
            spaces++;
        }
    }
    return spaces;
}


float countScore (float x, float y)
{
    float index = (0.0588 * x) - (0.296 * y) - 15.8;
    return index;
}


