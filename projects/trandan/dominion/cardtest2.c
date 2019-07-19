// to compile this file
// gcc -o cardtest2 dominion.c rngs.c cardtest2.c

#include "dominion.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "shuffle()"

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 1, currentPlayer = 0, i, j, it, randomCard, testRun = 100;
    int deckSize = 10;
    int similarDecks = 0;
    g.deckCount[0] = deckSize;
    int deckCopy[deckSize];
    int dupilcateDeck[100] = {0};
    
    printf(" Test 1: checking cards in deck are same before and after shuffle\n");
    for (j = 0; j < testRun; j++)
    {
        // assign deck with numbers 0 - 9
        for (i = 0; i < deckSize; i++)
        {
            g.deck[currentPlayer][i] = i;
            deckCopy[i] = i;

            ASSERT(g.deck[currentPlayer][i] == i, "error in deck assignment");
            ASSERT(g.deck[currentPlayer][i] == deckCopy[i], "deck copy is not a copy of g.deck");
        }

        ASSERT(shuffle(currentPlayer, &g) == 0, "Shuffle method returned error response");
        qsort(g.deck[currentPlayer], deckSize, sizeof(int), cmpfunc);

        for (i = 0; i < deckSize; i++)
        {
            ASSERT(g.deck[currentPlayer][i] == deckCopy[i], "Test 1 Failed ** deck cards are different");
        }
    }

    printf(" Test 2: check whether shuffled deck is same as ordered deck\n");
    for (j = 0; j < testRun; j++)
    {
        // assign deck with numbers 0 - 9
        for (i = 0; i < deckSize; i++)
        {
            g.deck[currentPlayer][i] = i;
            deckCopy[i] = i;

            ASSERT(g.deck[currentPlayer][i] == deckCopy[i], "deck copy is not a copy of g.deck");
            ASSERT(g.deck[currentPlayer][i] == i, "error in deck assignment");
        }

        ASSERT(shuffle(currentPlayer, &g) == 0, "Shuffle method returned error response");

        // check shuffled deck agaisnt unshuffled deck
        if (g.deck[currentPlayer][0] == deckCopy[0] 
        && g.deck[currentPlayer][1] == deckCopy[1] 
        && g.deck[currentPlayer][2] == deckCopy[2]
        && g.deck[currentPlayer][3] == deckCopy[3]
        && g.deck[currentPlayer][4] == deckCopy[4]
        && g.deck[currentPlayer][5] == deckCopy[5]
        && g.deck[currentPlayer][6] == deckCopy[6]
        && g.deck[currentPlayer][7] == deckCopy[7]
        && g.deck[currentPlayer][8] == deckCopy[8]
        && g.deck[currentPlayer][9] == deckCopy[9]
        )
        {
            similarDecks++;
        }
    }
    printf(" Similar decks found: %d  \n", similarDecks );
    printf("** Card test 2 concluded. **\n");
    return 0;
}
