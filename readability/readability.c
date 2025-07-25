#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// take in input from command line [argc,argv] {DON'T}
// you need to find the no. of sentences per 100 words and no of letters per 100 words
// set up counters and iterate trough every character in the input string
// every space = word++ & every '.,?,!' = sentence++
// return (make seperate functions to count words and sentences. or find out if a single function
// can return two variables)
// Math the Math
// Configure the output

// Functions Needed
// countSentence(. ! ?), countWords(already there argc-1), findScore

int countSentences(string x);
float countScore(float x, float y);
int countLetters(string x);
int countWords(string x);

int main(void)
{
    string ex = get_string("Text: ");
    int words = countWords(ex) + 1;
    int sentences = countSentences(ex);
    int letters = countLetters(ex);

    float l = ((float) letters / (float) words) * 100;
    float k = ((float) sentences / (float) words) * 100;

    float score = countScore(l, k);

    int level = round(score);

    // printf("%i\n", letters);
    // printf("%i\n", words); //prob
    // printf("%i\n", sentences);
    // printf("%f\n", score);
    // printf("%i\n", level);

    if (score <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (score >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}

int countSentences(string x)
{
    int sent = 0;

    for (int i = 0, len = strlen(x); i < len; i++)
    {
        char temp = x[i];
        if (temp == '.' || temp == '?' || temp == '!')
        {
            sent++;
        }
    }
    return sent;
}

int countLetters(string x)
{
    int letters = 0;

    for (int i = 0, len = strlen(x); i < len; i++)
    {
        if (isalpha(x[i]))
        {
            letters++;
        }
    }
    return letters;
}

int countWords(string x)
{
    int spaces = 0;

    for (int i = 0, len = strlen(x); i < len; i++)
    {
        if (x[i] == ' ')
        {
            spaces++;
        }
    }
    return spaces;
}

float countScore(float x, float y)
{
    float index = (0.0588 * x) - (0.296 * y) - 15.8;
    return index;
}
