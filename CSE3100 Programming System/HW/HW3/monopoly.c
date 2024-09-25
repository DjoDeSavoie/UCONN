#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// There will be m players in an array
typedef struct Player 
{
    int id;
    int loc;
    long balance;
} TPlayer;

// There will be n properties in an array
typedef struct Property
{
    int id;
    int owner_id;
    int rent;
} TProperty;

// Function to perform the transaction
int transaction(TPlayer *p1, TPlayer *p2, int amount)
{
    if (p1->balance >= amount)
    {
        p1->balance -= amount;
        p2->balance += amount;
        return 1; // Transaction successful
    }
    else
    {
        // Pay all balance and declare bankruptcy
        p2->balance += p1->balance;
        p1->balance = 0;
        return 0; // Transaction unsuccessful
    }
}

// Perform one round of the game
int one_round(int m, int n, TPlayer p[], TProperty prop[])
{
    for (int i = 0; i < m; i++)
    {
        // Roll two dice
        int steps = (rand() % 6 + 1) + (rand() % 6 + 1);
        p[i].loc = (p[i].loc + steps) % n; // Move to new location

        // Check if the player passed or landed on start (property 0)
        if (p[i].loc == 0)
        {
            p[i].balance += n; // Award $n when passing start
        }

        int loc = p[i].loc;
        if (prop[loc].owner_id == -1) // Property is unowned
        {
            // Player buys the property
            prop[loc].owner_id = p[i].id;
        }
        else if (prop[loc].owner_id != p[i].id) // Owned by someone else
        {
            int rent = prop[loc].rent;
            int owner_id = prop[loc].owner_id;
            if (!transaction(&p[i], &p[owner_id], rent)) // Transaction failed
            {
                return 0; // End game if the player can't pay
            }
        }
    }
    return 1; // Continue the game
}

// Used for printing out results
void print_result(int m, TPlayer p[])
{
    printf("      id    balance\n");
    for (int i = 0; i < m; i++)
    {
        printf("%8d %8ld\n", p[i].id, p[i].balance);
    }
    long sum = 0;
    long max = 0;
    for (int i = 0; i < m; i++)
    {
        sum += p[i].balance;
        if (p[i].balance > max) max = p[i].balance;
    }
    printf("average: %f max: %ld, max/average = %lf\n", (double)sum / m, max, (double)max * m / sum);
}

// max_rounds is needed because the game may never finish
void monopoly(int m, int n, TPlayer p[], TProperty prop[], int max_rounds)
{
    srand(12345);
    int rounds = 1;
    while (one_round(m, n, p, prop) && rounds < max_rounds)
    {
        rounds++;
    }
    print_result(m, p);
    printf("after %d rounds\n", rounds);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s m n rounds\n", argv[0]);
        return -1;
    }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int rounds = atoi(argv[3]);
    assert(n >= 13);
    assert(m >= 1);
    assert(rounds >= 1);

    TPlayer p[m];
    TProperty prop[n];

    // Initialize properties
    for (int i = 0; i < n; i++)
    {
        prop[i].id = i;
        prop[i].owner_id = -1; // No owner yet
        prop[i].rent = i + 1;  // Rent increases linearly
    }

    // Initialize players
    for (int j = 0; j < m; j++)
    {
        p[j].id = j;
        p[j].loc = 0; // All players start at property 0
        p[j].balance = n; // Initial balance is $n
    }

    monopoly(m, n, p, prop, rounds);
    return 0;
}
