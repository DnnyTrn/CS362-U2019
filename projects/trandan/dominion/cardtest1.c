// to compile this file
// gcc -o cardtest1 dominion.c rngs.c cardtest1.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "initializeGame()"

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 3, seed = 1;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, seed, &g);

    // Test check that each player deck has 3 estates, 7 copper
    printf(" Test 1: validating player decks \n");
    for (int i = 0; i < numPlayers; i++)
    {
        int coppers = 0, estates = 0;
        for (int j = 0; j < 10; j++)
        {
            if (g.deck[i][j] == copper)
                coppers++;
            else if(g.deck[i][j] == estate)
                estates++;
        }
        ASSERT(coppers == 7, "invalid copper count, should be 7");
        ASSERT(estates == 3, "invalid estate count, should be 3");
    }


    printf("** Card test 1 concluded. **\n");
    return 0;
}