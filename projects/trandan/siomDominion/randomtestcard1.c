// Danny Tran
// CS 362 * Assignment 4 * Random Test Card 1 (baron)
// to compile this file
// gcc -o randomtestcard1 dominion.c rngs.c randomtestcard1.c -Wall -fpic -coverage -lm -std=c99
// ./randomtestcard1
// gcov dominion -b
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTCARD "baron"

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

int asserttrue(int expr, char *error)
{
    if (!expr)
    {
        if(DEBUG) printf("Assertion failed: %s\n", error);
        return 1;
    }
    return 0;
}

// test oracle for playBaron
int checkPlayBaron(struct gameState *post, int currentPlayer, int choice1, int estateHandPosition)
{
    struct gameState pre;
    int p = estateHandPosition;
    memcpy(&pre, post, sizeof(struct gameState));
    ASSERT(memcmp(&pre, post, sizeof(struct gameState)) == 0, "memcpy failed coping pre and post states");
    ASSERT(baronEffect(post, choice1, currentPlayer) == 0, "playBaron did not return 0");

    pre.numBuys++;
    if (choice1 == 0)
    {
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = estate;
        pre.discardCount[currentPlayer]++;
        pre.supplyCount[estate]--;
    }
    else if (choice1 == 1 && estateHandPosition == -1)
    {
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = estate;
        pre.discardCount[currentPlayer]++;
        pre.supplyCount[estate]--;
    }
    else if (choice1 == 1)
    {
        pre.coins += 4;
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][p];
        pre.discardCount[currentPlayer]++;
        for (; p < pre.handCount[currentPlayer]; p++)
        {
            pre.hand[currentPlayer][p] = pre.hand[currentPlayer][p + 1];
        }
        pre.hand[currentPlayer][pre.handCount[currentPlayer]] = -1;
        pre.handCount[currentPlayer]--;
    }

    return asserttrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "memcmp return not 0");
}
int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int i, n, handCount, choice1, estateHandPosition = -1, testRun = 100, testsFailed = 0;
    int currentPlayer = 0;
    srand(time(0));

    for (n = 0; n < testRun; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&g)[i] = rand() % 256;
        }

        choice1 = rand() % 2;
        currentPlayer = rand() % MAX_PLAYERS;
        g.supplyCount[estate] = rand() % MAX_DECK + 1; 
        g.discardCount[currentPlayer] = rand() % MAX_DECK;
        g.handCount[currentPlayer] = rand() % MAX_HAND;
        handCount = g.handCount[currentPlayer];

        // 1 in 4 chances that the player will have an estate in their hand
        if (rand() % 4 == 0)
        {
            if (handCount == 0) // prevents mod by 0 error (floating point exception: 8)
            {
                estateHandPosition = 0;
                g.hand[currentPlayer][estateHandPosition] = estate;
            }
            else    //randomly assign estate to hand
            {
                estateHandPosition = rand() % handCount;
                g.hand[currentPlayer][estateHandPosition] = estate;
            }
        }
        else 
        {
            // ensure that no estates in player hand
            for (i = 0; i <= 10; i++)
            {
                g.hand[currentPlayer][i] = rand() % treasure_map + 2;
            }

            estateHandPosition = -1;
        }

        testsFailed += checkPlayBaron(&g, currentPlayer, choice1, estateHandPosition);
    }
    printf(" Tests Ran: %d \n", testRun);
    printf(" Tests Failed: %d \n", testsFailed);
    double failPercent = (double)testsFailed / (double)testRun * 100;
    printf(" Percent of tests failed %0.4lf%% \n", failPercent);
    printf("** Random test card 1 concluded. **\n");
    return 0;
}