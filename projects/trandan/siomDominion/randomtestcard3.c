// Danny Tran
// CS 362 * Assignment 4 * Random Test Card 3 (tribute)
// to compile this file
// gcc -o randomtestcard3 dominion.c rngs.c randomtestcard3.c -Wall -fpic -coverage -lm -std=c99

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TESTCARD "tribute"

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
    int handTest;
    int actionsTest;
    int testsFailed;
};

// initalize testCount struct members to 0
int testInit(struct testCount *t)
{
    t->actionsTest = 0;
    t->deckTest = 0;
    t->handTest = 0;
    t->coinTest = 0;
    t->testsFailed = 0;
    return 0;
}

// returns number of tests failed in struct testCount and updates the testCount member testsFailed
int updateTestFailCount(struct testCount *t)
{
    return t->testsFailed = t->actionsTest + t->deckTest + t->handTest + t->coinTest;
}

// prints the count of tests failed
void printTestCount(struct testCount *t)
{
    printf(" Deck Test failed: %d \n", t->deckTest);
    printf(" Hand Test failed: %d \n", t->handTest);
    printf(" Coin Test failed: %d \n", t->coinTest);
    printf(" Action Test failed: %d \n", t->actionsTest);
}

// test oracle for playTribute
// check if tributed cards gives players their benefits
int checkPlayTribute(struct gameState *post, int nextPlayer, int *tributeRevealedCards, int currentPlayer, struct testCount *t)
{
    struct gameState pre;
    int i;
    memcpy(&pre, post, sizeof(struct gameState));
    ASSERT(memcmp(&pre, post, sizeof(struct gameState)) == 0, "memcpy failed coping pre and post states");

    ASSERT(tributeEffect(post, currentPlayer, nextPlayer, tributeRevealedCards) == 0, "playTribute did not return 0");

    for (i = 0; i < 2; i++)
    {
        // player gains 2 coins for cards that are copper (4), silver (5) or gold (6)
        if (tributeRevealedCards[i] >= copper && tributeRevealedCards[i] <= gold)
        {
            pre.coins += 2;
        }
        // player gains 2 cards, update pre-state that deck/hand/discard counts reflect transaction
        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
        {
            pre.deckCount[currentPlayer] -= 2;
            pre.handCount[currentPlayer] += 2;
        }
        else
        {
            pre.numActions += 2;
        }
    }

    t->coinTest += asserttrue(pre.coins == post->coins, "coins are different");
    t->deckTest += asserttrue(pre.deckCount[currentPlayer] == post->deckCount[currentPlayer], "deckCounts are different");
    t->handTest += asserttrue(pre.handCount[currentPlayer] == post->handCount[currentPlayer], "handCounts are different");
    t->actionsTest += asserttrue(pre.numActions == post->numActions, "numActions are different");

    return 0;
}

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    struct testCount t;
    testInit(&t);
    int i, j, n, testRun = 10000, currentPlayer, nextPlayer;
    int tributedRevealedCards[] = {};
    srand(time(0));
    for (n = 0; n < testRun; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&g)[i] = rand() % 256;
        }

        // initialize cards and card counts for 4 players
        for (i = 0; i < MAX_PLAYERS; i++)
        {
            for (j = 0; j < MAX_DECK; j++)
            {
                g.hand[i][j] = rand() % 256;
                g.deck[i][j] = rand() % 256;
                g.discard[i][j] = rand() % 256;
            }

            g.handCount[i] = MAX_DECK;
            g.deckCount[i] = rand() % MAX_DECK;
            g.discardCount[i] = rand() % MAX_DECK;
        }

        g.playedCardCount = rand() % MAX_DECK;

        // reduces deckCount test failures to 0 since randomizing current and nextPlayer goes against the logic of Tribute card
        // currentPlayer = 0;
        // nextPlayer = 1;

        // randomize current and nextPlayer (goes against Tribute logic)
        currentPlayer = rand() % MAX_PLAYERS;
        nextPlayer = rand() % MAX_PLAYERS;

        // make sure players are not the same number
        if (nextPlayer == currentPlayer && nextPlayer == 3)
        {
            nextPlayer = rand() % 3;
        }
        else if (nextPlayer == currentPlayer && nextPlayer == 0)
        {
            nextPlayer = (rand() % (MAX_PLAYERS - 1)) + 1;
        }
        else if (nextPlayer == currentPlayer)
            nextPlayer++;

        checkPlayTribute(&g, nextPlayer, tributedRevealedCards, currentPlayer, &t);
    }

    updateTestFailCount(&t);
    printf(" Tests Ran: %d \n", testRun);
    printf(" Tests Failed: %d \n", t.testsFailed);
    printTestCount(&t);
    double failPercent = (double)t.testsFailed / (double)testRun * 100;
    printf(" Percent of tests failed %0.4lf%% \n", failPercent );
    printf("** Random test card 3 concluded. **\n");
    return 0;
}