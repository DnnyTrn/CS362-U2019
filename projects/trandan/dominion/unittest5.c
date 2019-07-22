// to compile this file
// gcc -o unittest5 dominion.c rngs.c unittest5.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "ambassador"

int initialize(int numPlayers, struct gameState *state, int *deck, int deckSize)
{
    int i, j;
    state->numPlayers = numPlayers;
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
    for (i = 0; i < numPlayers; i++)
    {
        //initialize hand size to zero
        state->handCount[i] = 0;
        state->discardCount[i] = 0;
        // draw 5 cards
        for (j = 0; j < 5; j++)
        {
            drawCard(i, state);
        }
    }

    //initialize supply
    ///////////////////////////////

    //set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }

    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;
    return 0;
}

int main()
{
    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 2, currentPlayer = 0, choice1 = 1, choice2, handPos = 0;
    int deck[10] = {copper, silver, gold, estate, duchy, province, gardens, great_hall, curse, baron};
    int deckSize = 10;
    // testing branch coverage, testing part 1
    printf(" Testing branches of playAmbassador() \n");
    choice2 = -1;
    ASSERT(playAmbassador(&g, choice1, currentPlayer, choice2, handPos) == -1, "playAmbassador assertion failed choice2 must be 1");

    choice2 = 1, choice1 = handPos;
    ASSERT(playAmbassador(&g, choice1, currentPlayer, choice2, handPos) == -1, "playAmbassador assertion failed choice1 cannot equal handPos");

    choice1 = 1;
    ASSERT(playAmbassador(&g, choice1, currentPlayer, choice2, handPos) == -1, "playAmbassador assertion failed j < choice2");

    initialize(numPlayers, &g, deck, deckSize);
    g.hand[currentPlayer][choice1] = 4;
    ASSERT(playAmbassador(&g, choice1, currentPlayer, choice2, handPos) == 0, "playAmbassador assertion failed, expected return 0");

    printf("** Unit test 5 concluded. **\n");
    return 0;
}