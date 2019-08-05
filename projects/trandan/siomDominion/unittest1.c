// to compile this file
// gcc -o unittest1 dominion.c rngs.c unittest1.c
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "baron"

int main()
{
    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    // initialization variables
    int numPlayers = 2, seed = 1, choice1 = 1, currentPlayer = 1;

    struct gameState test_game;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, seed, &test_game);

    // Test variables
    int preStateBuy = test_game.numBuys;       //buy count = 1
    int preStateCoins = test_game.coins;       //coins = 4
    test_game.hand[currentPlayer][0] = estate; // player +1 estate for testing purposes

    // Test 1 playBaron() returns 0 for successful execution
    printf("Test 1: Testing playBaron() for execution\n");
    ASSERT(baronEffect(&test_game, choice1, currentPlayer) == 0, "playBaron() did not return 0");

    // Test 2: Expected Buy count is 2 reguardless of choice1 value
    int buyCount = test_game.numBuys;
    int expectedBuyCount = 2;
    printf("Test 2: BUY COUNT is %d; Expected BUY COUNT is %d \n", buyCount, expectedBuyCount);
    ASSERT(buyCount == preStateBuy + 1 && buyCount == expectedBuyCount, "Test 2: FAILED ** BUY COUNT is not correct value");

    //  ** Choice 1 Testing (3 - 5): current player has -1 estate and +4 additional coins, game state has +1 estate. **

    //Test 3: choice1 = 1 | player: +4 coins |
    int coinCount = test_game.coins;
    int expectedCoinCount = 8;
    printf("Test 3: COIN COUNT is %d; Expected COIN COUNT is %d \n", coinCount, expectedCoinCount);
    ASSERT(coinCount == expectedCoinCount && preStateCoins + 4 == coinCount, "Test 3: FAILED ** COIN COUNT is not correct value");

    //Test 4: choice1 = 1 | player: -1 estate |
    // int estateCount = test_game.supplyCount[estate];
    printf("Test 4: Checking player's estate count\n");
    ASSERT(test_game.hand[currentPlayer][0] != estate, "Test 4: FAILED ** ESTATE not discarded");
    // player should not have estate in hand (given from line 29)

    //Test 5: choice1 = 1 |game state : +1 estate |
    int expectedEstateCount = 9;
    printf("Test 5: ESTATE COUNT is %d; Expected ESTATE COUNT is %d \n", test_game.supplyCount[estate], expectedEstateCount);
    ASSERT(expectedEstateCount == test_game.supplyCount[estate], "Test 5: FAILED ** game state ESTATE count is incorect");

    // ** Choice 2 Testing **
    int choice2 = 0;
    struct gameState test_game2;
    baronEffect(&test_game2, choice2, currentPlayer);

    //Test 6 (repeat of Test 2 for buy count)
    buyCount = test_game.numBuys;
    expectedBuyCount = 2;
    printf("Test 6: BUY COUNT is %d; Expected BUY COUNT is %d \n", buyCount, expectedBuyCount);
    ASSERT(buyCount == preStateBuy + 1 && buyCount == expectedBuyCount, "Test 2: FAILED ** BUY COUNT is not correct value");

    //Test 7 check player estate count
    printf(" discard count count %d\n", test_game2.discardCount[currentPlayer]);
    for (int i = 0; i < 3; i++)
    {
        printf("card: %d \n", test_game2.discard[currentPlayer][i]);
    }

    printf("** Unit test 1 concluded.\n");
    return 0;
}