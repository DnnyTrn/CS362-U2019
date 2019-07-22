// to compile this file
// gcc -o cardtest5 dominion.c rngs.c cardtest5.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "drawCards()"

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 4, i, testRun = 1000;
    int currentPlayer = 0;
    srand(time(0));

    printf(" Test 1: Calling drawCard with empty deck and discard pile \n");
    g.deckCount[currentPlayer] = 0;
    ASSERT(drawCard(currentPlayer, &g) == -1, "Test 1 failed, drawCard did not return -1");
    ASSERT(g.discardCount[currentPlayer] == 0, "Test 1 failed, discard count is not 0");
    ASSERT(g.deckCount[currentPlayer] == 0, "Test 1 failed, deck count is not 0");

    printf(" Test 2: Random testing of drawCard \n");
    for (i = 0; i < testRun; i++)
    {
        for (currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
        {
            g.handCount[currentPlayer] = rand() % MAX_HAND;
            g.deckCount[currentPlayer] = rand() % MAX_DECK + 1;
            g.discardCount[currentPlayer] = rand() % MAX_DECK;
            ASSERT(drawCard(currentPlayer, &g) == 0, "Test 2 failed, drawCard did not return 0");
        }
    }

    printf("** Card test 5 concluded. **\n");
    return 0;
}
