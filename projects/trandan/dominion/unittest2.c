// Danny Tran
// CS 362
// to compile this file
// gcc -o unittest2 dominion.c rngs.c unittest2.c -Wall -fpic -coverage -lm -std=c99
// ./unittest2

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

// used to intialize gameState for testing
void createTestGame(struct gameState *cardTestGame, int cardName)
{
    int numPlayers = 4, randomSeed = rand();
    int kingdomCards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                            sea_hag, tribute, smithy};

    initializeGame(numPlayers, kingdomCards, randomSeed, cardTestGame);
}

int tributeEffect(struct gameState *pre, int currentPlayer)
{
    if (currentPlayer < 0 || currentPlayer > MAX_PLAYERS)
        return -1;

    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > (pre->numPlayers - 1))
    {
        nextPlayer = 0;
    }

    int i;
    // simulate tribute card on pre game state
    int tributeRevealedCards[2] = {-1, -1};
    tributeRevealedCards[0] = pre->deck[nextPlayer][pre->deckCount[nextPlayer] - 1];
    pre->deck[nextPlayer][pre->deckCount[nextPlayer]--] = -1;
    pre->deckCount[nextPlayer]--;
    tributeRevealedCards[1] = pre->deck[nextPlayer][pre->deckCount[nextPlayer] - 1];
    pre->deck[nextPlayer][pre->deckCount[nextPlayer]--] = -1;
    pre->deckCount[nextPlayer]--;

    if (tributeRevealedCards[0] == tributeRevealedCards[1])
    { //If we have a duplicate card, just drop one
        pre->playedCards[pre->playedCardCount] = tributeRevealedCards[1];
        pre->playedCardCount++;
        tributeRevealedCards[1] = -1;
    }

    for (i = 0; i < 2; i++)
    {
        if (tributeRevealedCards[i] == curse)
            continue;

        if (tributeRevealedCards[1] == -1)
            break;

        // player gains 2 coins for cards that are copper (4), silver (5) or gold (6)
        if (tributeRevealedCards[i] >= copper && tributeRevealedCards[i] <= gold)
        {
            pre->coins += 2;
        }
        // player gains 2 cards, update pre-state that deck/hand/discard counts reflect transaction
        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
        {
            pre->deckCount[currentPlayer] -= 2;
            pre->handCount[currentPlayer] += 2;
        }
        else
        {
            pre->numActions += 2;
        }
    }
    return 0;
}
void testBaron1()
{
    printf("----------------- Testing Card: %s ----------------\n", "baron");

    int cardName = baron, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;

    // create test game
    struct gameState state;
    createTestGame(&state, cardName);
    int preSupplyCountEstate = state.supplyCount[estate]; //keep track of supplyCount[estate] before playing baron

    // play baron card
    // set player 1 card 1 to card being played
    state.hand[0][0] = baron;
    playCard(handPos, choice1, choice2, choice3, &state);

    // validate supply count estate
    ASSERT(state.supplyCount[estate] == preSupplyCountEstate - 1, "supplyCount[estate] should be 11");
    printf("supplyCount[estate]: %d \n", state.supplyCount[estate]);
    printf("----------------- End of Testing Card: %s ----------------\n", "baron");
}

void testTribute1()
{
    printf("----------------- Testing Card: %s ----------------\n", "tribute");

    int cardName = tribute, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int currentPlayer = 0;

    // create test game
    struct gameState state, pre;
    createTestGame(&state, cardName);
    memcpy(&pre, &state, sizeof(struct gameState));

    // play tribute card
    cardEffect(cardName, choice1, choice2, choice3, &state, handPos, &bonus);

    // tribute effect on pre state
    tributeEffect(&pre, currentPlayer);

    // validate pre state against the post game state
    ASSERT(pre.coins == state.coins, "pre and post state coins are different");
    printf(" pre state coins: %d  \n", pre.coins);
    printf(" post state coins: %d \n", state.coins);

    ASSERT(pre.deckCount[currentPlayer] == state.deckCount[currentPlayer], "pre and post state deckCounts are different");
    printf(" pre state deckCount[currentPlayer]: %d  \n", pre.deckCount[currentPlayer]);
    printf(" post state deckCount[currentPlayer]: %d \n", state.deckCount[currentPlayer]);

    ASSERT(pre.handCount[currentPlayer] == state.handCount[currentPlayer], "pre and post state handCounts are different");
    printf(" pre state handCount[currentPlayer]: %d  \n", pre.handCount[currentPlayer]);
    printf(" post state handCount[currentPlayer]: %d \n", state.handCount[currentPlayer]);

    ASSERT(pre.numActions == state.numActions, "pre and post state numActions are different");
    printf(" pre state numActions: %d  \n", pre.numActions);
    printf(" post state numActions: %d \n", state.numActions);

    printf("----------------- End of Testing Card: %s ----------------\n", "tribute");
}
void testTribute2()
{
    printf("----------------- Testing Card: %s ----------------\n", "tribute");

    int i, cardName = tribute, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int currentPlayer = 0, nextPlayer = 1;

    // create test game
    struct gameState state, pre;
    createTestGame(&state, cardName);

    // give next player only curse cards
    for (i = 0; i < state.deckCount[nextPlayer]; i++)
    {
        state.deck[nextPlayer][i] = curse;
    }

    memcpy(&pre, &state, sizeof(struct gameState));

    // play tribute card on post game state
    cardEffect(cardName, choice1, choice2, choice3, &state, handPos, &bonus);

    // tribute effect on pre state
    tributeEffect(&pre, currentPlayer);

    // validate pre state against the post game state
    ASSERT(pre.coins == state.coins, "pre and post state coins are different");
    printf(" pre state coins: %d  \n", pre.coins);
    printf(" post state coins: %d \n", state.coins);

    ASSERT(pre.deckCount[currentPlayer] == state.deckCount[currentPlayer], "pre and post state deckCounts are different");
    printf(" pre state deckCount[currentPlayer]: %d  \n", pre.deckCount[currentPlayer]);
    printf(" post state deckCount[currentPlayer]: %d \n", state.deckCount[currentPlayer]);

    ASSERT(pre.handCount[currentPlayer] == state.handCount[currentPlayer], "pre and post state handCounts are different");
    printf(" pre state handCount[currentPlayer]: %d  \n", pre.handCount[currentPlayer]);
    printf(" post state handCount[currentPlayer]: %d \n", state.handCount[currentPlayer]);

    ASSERT(pre.numActions == state.numActions, "pre and post state numActions are different");
    printf(" pre state numActions: %d  \n", pre.numActions);
    printf(" post state numActions: %d \n", state.numActions);

    printf("----------------- End of Testing Card: %s ----------------\n", "tribute");
}

int main()
{
    printf(" \n Unit Testing of dominionFix.c \n");
    srand(time(0));
    testTribute1();
    testBaron1();
    testTribute2();
}
