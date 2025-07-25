#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // Input is vote by the person 'name'
    // need to check if it is present in the candidates array.
    // make name and check cand array case insensitive by forcing upper or lower string function
    // if present, take pointer value to find cand[i] and increment it's vote value

    // iterate through every candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        // compare string, if match, increase respective counter
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // Default case
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // after all votes are cast, every cand[i] will have it's respective votes declared globally
    // compare all candidates.votes[i] and print the highest one
    int temp_vote = candidates[0].votes;
    // Iterate through every candidate vote
    for (int i = 1; i < candidate_count; i++)
    {
        // if next is smaller than prev, change and assign new values
        if ((candidates[i].votes > candidates[i - 1].votes))
        {
            temp_vote = candidates[i].votes;
        }
    }

    // print winners
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == temp_vote)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}
