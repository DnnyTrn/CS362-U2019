// to compile this file
// gcc -o unittest2 dominion.c rngs.c unittest2.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "minion"

int main()
{
    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState test_game;
    int numPlayers = 2, seed = 1, choice1 = 1, choice2 = 0, currentPlayer = 0;
    int minionHandPos = 0;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, seed, &test_game);
    int handCount = test_game.handCount[currentPlayer]; 

    //put minion card in player handPos 0
    test_game.hand[currentPlayer][0] = minion;
    playMinion(&test_game, choice1, currentPlayer, choice2, minionHandPos);

    //Test 1: Player's actions +1

    //Test 2: check hand for minion card, minion is discarded after play
        // printf(" card before %d %d\n ",i, hand[i] );
    int currentCard;
    for (int i = 0; i < handCount; i++)
    {
        currentCard = test_game.hand[currentPlayer][i];
        ASSERT(currentCard != minion, "Test 2 failed, minion card still in hand");
    }

    
    printf("** Unit test 2 concluded. **\n");
    return 0;
}