// to compile this file
// gcc -o unittest3 dominion.c rngs.c unittest3.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "tribute"

int initialize(int numPlayers, struct gameState *state, int *deck, int deckSize)
{
    int i, j;
    //set player decks
    for (i = 0; i < numPlayers; i++)
    {
        state->deckCount[i] = 0;

        for (j = 0; j < deckSize; j++)
        {
            state->deck[i][j] = deck[j];
            state->deckCount[i]++;
        }
    }

    //shuffle player decks
    for (i = 0; i < numPlayers; i++)
    {
        if (shuffle(i, state) < 0)
        {
            return -1;
        }
    }
    state->playedCardCount = 0;

    return 0;
}

int main()
{
    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 2, currentPlayer = 0, nextPlayer = 1, i, j, k, testRun = 1000, deckSize;
    int tributeRevealedCards[2];

    printf(" Test 1: testing branch coverage with alternating decks\n");

    // Testing with deck with only treasure cards
    int treasure_deck[9] = {copper, silver, gold, copper, silver, gold, copper, silver, gold};
    deckSize = 9;
    for (i = 0; i < testRun; i++)
    {
        ASSERT(initialize(numPlayers, &g, treasure_deck, deckSize) == 0, "initialize failed");
        ASSERT(playTribute(&g, nextPlayer, tributeRevealedCards, currentPlayer) == 0, "playTribute did not return 0");
    }

    // Testing with deck with only victory cards
    int victory_deck[10] = {estate, duchy, province, gardens, great_hall, estate, duchy, province, gardens, great_hall};
    deckSize = 10;
    for (i = 0; i < testRun; i++)
    {
        ASSERT(initialize(numPlayers, &g, victory_deck, deckSize) == 0, "initialize failed");
        ASSERT(playTribute(&g, nextPlayer, tributeRevealedCards, currentPlayer) == 0, "playTribute did not return 0");
    }

    // Testing with deck with only action cards
    int action_deck[8] = {minion, baron, tribute, ambassador, minion, baron, tribute, ambassador};
    deckSize = 8;
    for (i = 0; i < testRun; i++)
    {
        ASSERT(initialize(numPlayers, &g, action_deck, deckSize) == 0, "initialize failed");
        ASSERT(playTribute(&g, nextPlayer, tributeRevealedCards, currentPlayer) == 0, "playTribute did not return 0");
    }

    // Test 2: testing branch coverage with no decks
    printf(" Test 2: testing branch coverage with no decks\n");
    for (i = 0; i < testRun; i++)
    {
        for (j = 0; j < 2; j++)
        {
            g.discardCount[nextPlayer] = j;
            for (k = 0; k < 2; k++)
            {
                g.deckCount[nextPlayer] = k;
                ASSERT(playTribute(&g, nextPlayer, tributeRevealedCards, currentPlayer) == 0, "playTribute did not return 0");
            }
        }
    }
    printf("** Unit test 3 concluded. **\n");
    return 0;
}
