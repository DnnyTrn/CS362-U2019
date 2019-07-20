// to compile this file
// gcc -o cardtest3 dominion.c rngs.c cardtest3.c

#include "dominion.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "endTurn()"

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    int numPlayers = 4, handCount = 5, i, j, k, testRun = 100;
    initializeGame(numPlayers, cards, 1, &g);

    printf("Test 1: Test to see if previous player’s hand is discarded after endTurn.\n");
    printf("Test 2: Testing for correct player turn\n");
    printf("Test 3: Testing for correct player variables intialization\n");
    for (i = 0; i < testRun; i++)
    {
        for (j = 0; j < numPlayers; j++)
        {
            ASSERT(j == g.whoseTurn, "Test 2 failed: error in determining next player");
            ASSERT(g.handCount[j] == 5, " handCount");  //current player should have 5 cards

            endTurn(&g);
            // testing the player's initialization variables set by endTurn
            ASSERT(g.outpostPlayed == 0, "current player outpostPlayed is not set to 0");
            ASSERT(g.phase == 0, " current player phase is not set to 0");
            ASSERT(g.numActions == 1, "current player numActions is not set to 1");
            ASSERT(g.numBuys == 1, "current player numBuys is not set to 1");
            ASSERT(g.playedCardCount == 0, "current player playedCardCount is not set to 0");

            // checking for previous player hand is discarded/empty
            for (k = 0; k < handCount; k++)
                ASSERT(g.hand[j][k] == -1, "Test 1 failed: Previous player's hand was not discarded");
        }
    }
    printf("** Card test 3 concluded. **\n");
    return 0;
}
