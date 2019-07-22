// to compile this file
// gcc -o unittest4 dominion.c rngs.c unittest4.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "mine"

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

// // print hand
//     for (i = 0; i < g.handCount[currentPlayer]; i++)
//         printf(" %d %d \n", i, g.hand[currentPlayer][i]);
    return 0;
}

int main()
{
    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 1, currentPlayer = 0, choice1 = 1, choice2 = 2, handPos = 0, deckSize;

// testing branch coverage, testing part 1
printf(" Testing branches of playMine() \n" );
    g.hand[currentPlayer][choice1] = copper - 1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == -1, "playMine did not return -1");
    g.hand[currentPlayer][choice1] = gold + 1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == -1, "playMine did not return -1");

    g.hand[currentPlayer][choice1] = copper;
    choice2 = treasure_map + 1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == -1, "playMine did not return -1");
    choice2 = curse - 1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == -1, "playMine did not return -1");

    choice1 = 1, choice2 = 0;
    g.hand[currentPlayer][choice1] = copper;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == -1, "playMine did not return -1");

// testing part 2 of mine card effect
    printf(" Testing Mine card effects \n");
    int treasure_deck[9] = {copper, silver, gold, copper, silver, gold, copper, silver, gold};
    deckSize = 9;

// testing that player recieves gold for silver
    ASSERT(initialize(numPlayers, &g, treasure_deck, deckSize) == 0, "initialize failed");
    choice1 = 1, choice2 = gold;
    g.hand[currentPlayer][choice1] = silver;
    handPos = choice1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == 0, "playMine did not return 0");
    ASSERT(g.hand[currentPlayer][choice1] != silver, "player's choice was not discarded properly by playMine");

// testing that player recieves silver for copper
    ASSERT(initialize(numPlayers, &g, treasure_deck, deckSize) == 0, "initialize failed");
    choice1 = 1, choice2 = silver;
    g.hand[currentPlayer][choice1] = copper;
    handPos = choice1;
    ASSERT(playMine(&g, currentPlayer, choice1, choice2, handPos) == 0, "playMine did not return 0");
    ASSERT(g.hand[currentPlayer][choice1] != copper, "player's choice was not discarded properly by playMine");

    printf("** Unit test 4 concluded. **\n");
    return 0;
}