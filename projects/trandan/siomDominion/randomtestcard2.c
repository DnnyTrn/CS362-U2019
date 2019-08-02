// Danny Tran
// CS 362 * Assignment 4 * Random Test Card 2 (minion)
// to compile this file
// gcc -o randomtestcard2 dominion.c rngs.c randomtestcard2.c -Wall -fpic -coverage -lm -std=c99
// ./randomtestcard2
// gcov dominion -b
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTCARD "minion"
// Assert for printing error messages, but can slow down testing
#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

// returns 1 if expression is false, and prints the passed error message
// function can be coupled to keep track of test failures
int asserttrue(int expr, char *error)
{
    if (!expr)
    {
        if (DEBUG)
            printf("Assertion failed: %s\n", error);
        return 1;
    }
    return 0;
}
// keeps track of individual test failures
struct testCount
{
    int coinTest;
    int deckTest;
    int discardTest;
    int handTest;
    int actionsTest;
    int testsFailed;
};

// initalize testCount struct members to 0
int testInit(struct testCount *t)
{
    t->actionsTest = 0;
    t->deckTest = 0;
    t->discardTest = 0;
    t->handTest = 0;
    t->coinTest = 0;
    t->testsFailed = 0;
    return 0;
}
// returns number of tests failed in struct testCount and updates the testCount member testsFailed
int updateTestFailCount(struct testCount *t)
{
    return t->testsFailed = t->actionsTest + t->deckTest + t->handTest + t->coinTest + t->discardTest;
}

// prints the count of tests failed
void printTestCount(struct testCount *t)
{
    printf(" Deck Count Test failed: %d \n", t->deckTest);
    printf(" Hand Count Test failed: %d \n", t->handTest);
    printf(" Coin Test failed: %d \n", t->coinTest);
    printf(" Action Test failed: %d \n", t->actionsTest);
}

// test oracle for playBaron
int checkPlayMinion(struct gameState *post, int choice1, int choice2, int currentPlayer, int handPos, struct testCount *t)
{
    struct gameState pre;
    int i, j;
    memcpy(&pre, post, sizeof(struct gameState));
    ASSERT(memcmp(&pre, post, sizeof(struct gameState)) == 0, "memcpy failed coping pre and post states");
    ASSERT(minionEffect(post, choice1, choice2, handPos, currentPlayer) == 0, "playMinion did not return 0");

    pre.numActions++;
    discardCard(handPos, currentPlayer, &pre, 0);
    if (choice2)
    {
        pre.coins = pre.coins + 2;
    }
    else if (choice1)
    {
        while (pre.handCount[currentPlayer] > 0)
        {
            pre.handCount[currentPlayer]--;
        }
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, &pre);
        }
        for (i = 0; i < pre.numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                if (pre.handCount[i] > 4)
                {
                    while (pre.handCount[i] > 0)
                    {
                        discardCard(handPos, i, &pre, 0);
                    }
                    for (j = 0; j < 4; j++)
                    {
                        drawCard(i, &pre);
                    }
                }
            }
        }
    }

    t->coinTest += asserttrue(pre.coins == post->coins, "coins are different");
    t->actionsTest += asserttrue(pre.numActions == post->numActions, "numActions are different");
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        t->discardTest += asserttrue(pre.discardCount[i] == post->discardCount[i], "discard count are different");
        t->deckTest += asserttrue(pre.deckCount[i] == post->deckCount[i], "deckCounts are different");
        t->handTest += asserttrue(pre.handCount[i] == post->handCount[i], "handCounts are different");
    }
    return 0;
}
int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    struct testCount t;
    testInit(&t);

    int i, n, j, k, handCount, choice1, choice2, handPos, testRun = 100;
    int currentPlayer = 0;
    srand(time(0));
    for (n = 0; n < testRun; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&g)[i] = rand() % 256;
        }
        for (j = 0; j < MAX_PLAYERS; j++)
        {
            // randomize hand, deck and discards for 4 players to numbers 0 - 255
            for (k = 0; k < MAX_DECK; k++)
            {
                g.hand[j][k] = rand() % 256;
                g.deck[j][k] = rand() % 256;
                g.discard[j][k] = rand() % 256;
            }
            g.handCount[j] = rand() % MAX_DECK;
            g.deckCount[j] = rand() % MAX_DECK;
            g.discardCount[j] = rand() % MAX_DECK;
        }
        choice1 = rand() % 256;
        choice2 = rand() % 256;
        currentPlayer = rand() % MAX_PLAYERS;
        g.whoseTurn = currentPlayer;
        g.playedCardCount = 0;
        g.numPlayers = MAX_PLAYERS;

        handCount = g.handCount[currentPlayer];
        //set handPos
        if (handCount == 0)
        {
            handPos = 0;
        }
        else
            handPos = rand() % handCount;

        checkPlayMinion(&g, choice1, choice2, currentPlayer, handPos, &t);
    }

    updateTestFailCount(&t);
    printf(" Tests Ran: %d \n", testRun);
    printf(" Tests Failed: %d \n", t.testsFailed);
    printTestCount(&t);
    double failPercent = (double)t.testsFailed / (double)testRun * 100;
    printf(" Percent of tests failed %0.4lf%% \n", failPercent);
    printf("** Random test card 2 concluded. **\n");
    return 0;
}