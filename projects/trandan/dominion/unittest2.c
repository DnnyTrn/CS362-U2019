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
    int numPlayers = 2, seed = 1, choice1 = 1, choice2 = 2, currentPlayer = 0;
    int minionHandPos = 0;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, seed, &test_game);
    int handCount = test_game.handCount[currentPlayer];
    int preStateCoins = test_game.coins;
    int preStateNumAction = test_game.numActions;
    int preStateDiscardCount = test_game.discardCount[currentPlayer];
    // printf(" discardcount %d \n ", preStateDiscardCount );
    //put minion card in player handPos 0
    test_game.hand[currentPlayer][0] = minion;


    playMinion(&test_game, choice1, currentPlayer, minionHandPos);

    //Test 1: Player's actions +1
    int expectedNumAction = preStateNumAction + 1;
    int numActions = test_game.numActions;
    printf("Test 1: Player Actions is %d, Expected Actions is %d \n", numActions, expectedNumAction);
    ASSERT(numActions == expectedNumAction, "Test 1 failed, number of actions is not correct value");

    //Test 2: check hand for minion card, minion is discarded after play
        // printf(" card before %d %d\n ",i, hand[i] );
    printf("Test 2: checking hand for minion card, minion should be discarded from hand\n");
    int currentCard;
    for (int i = 0; i < handCount; i++)
    {
        currentCard = test_game.hand[currentPlayer][i];
        ASSERT(currentCard != minion, "Test 2 failed, minion card still in hand");
    }
    printf(" playedCardCount++; %d \n ", test_game.playedCardCount);
    // ASSERT(test_game.playedCardCount == 0, "Test 2 failed, state played card count is incorrect value");

    //Test 3: check if choice1 gives player +2 coins
    int coinCount = test_game.coins;
    int expectedCoinCount = 6;
    printf("Test 3: COIN COUNT is %d; Expected COIN COUNT is %d \n", coinCount, expectedCoinCount);
    ASSERT(choice1 == 1, "Test 3: choice1 variable is not 1 which designates this path");
    ASSERT(coinCount == expectedCoinCount, "Test 3: FAILED ** COIN COUNT does not match expectedCoinCount");
    ASSERT(preStateCoins + 2 == coinCount, "Test 3: FAILED ** preStateCoins + 2 does not match coinCount");

    // Test 4:

    printf(" discardcount %d \n ", test_game.discardCount[currentPlayer]);

    printf("** Unit test 2 concluded. **\n");
    return 0;
}