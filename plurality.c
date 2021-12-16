#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

/*
Print the winner (or winners) of the election
This function re-arranges the candidates'
data in ascending order of the number of votes
for each candidate.
*/
void print_winner(void)
{

    /*
    These variables carry values temporarily,
    The values that these variables carry will be used
    during the filtering process.
    */
    
    string name;
    int vote;
    
    /*
    Here the iterative loop begins
    Note the episode here starting from number one
    Then a comparison begins with the number of candidate[i].votes
    as to whether it is greater than or equal to the number of candidate[0].votes,
    Then the program starts making the right decisions
    */
    for (int i = 1; i < candidate_count; i++)
    {
        
        if (candidates[i].votes > candidates[0].votes)
        {
            name = candidates[0].name;
            vote = candidates[0].votes;
            
            candidates[0].name = candidates[i].name;
            candidates[0].votes = candidates[i].votes;
            
            candidates[i].name = name;
            candidates[i].votes = vote;
        }
        else if (candidates[i].votes == candidates[0].votes)
        {
            
            name = candidates[1].name;
            vote = candidates[1].votes;
            
            candidates[1].name = candidates[i].name;
            candidates[1].votes = candidates[i].votes;
            
            candidates[i].name = name;
            candidates[i].votes = vote;
            
        }

    }
    
    /*
    Print the name of the first winner
    and then check if there are other winners or not
    */
    if (candidates[0].votes > candidates[1].votes)
    {
        printf("%s\n", candidates[0].name);

    }
    
    // if there are multiple winners
    else
    {
        printf("%s\n", candidates[0].name);
        
        // Print the names of the remaining winners
        for (int i = 1; i < candidate_count; i++)
        {
            if (candidates[0].votes == candidates[i].votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }
        
    }
    return ;
}

