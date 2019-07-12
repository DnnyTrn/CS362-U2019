// to compile this file
// gcc -o unittest1 dominion.c rngs.c unittest1.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include "compare.h"
#define TESTCARD "baron"



int main()
{
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    int numPlayers = 2, seed = 1, choice1 = 1, choice2, currentPlayer = 1;

    struct gameState test_game;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, seed, &test_game);
    printf(" coincount %d \n ", test_game.coins);

    // after initialization, players start with ..
    int preStateBuy = test_game.numBuys; //buy count = 1
    int preStateCoins = test_game.coins; //coins = 4

    // Test 1 playBaron() returns 0 for successful execution
    if (isSame(playBaron(&test_game, choice1, currentPlayer), 0))
        printf("calling playBaron()\n");
    else
        printf("playBaron() failed\n");

    // Test 2: Expected Buy count is 2 reguardless of choice1 value
    int buyCount = test_game.numBuys;
    int expectedBuyCount = 2;
    if (isSame(buyCount, preStateBuy + 1) && assertTrue(buyCount == expectedBuyCount))
        printf("Test 1 : PASSED ** BUY COUNT is %d; Expected BUY COUNT is %d \n", buyCount, expectedBuyCount);
    else
        printf("Test 1 : FAILED ** BUY COUNT is %d; Expected BUY COUNT is %d \n", buyCount, expectedBuyCount);

    //  ** Choice 1 Testing (3 - 5): current player has -1 estate and +4 additional coins, game state has +1 estate. **
    //Test 3: choice1 = 1 | player: +4 coins |
    int coinCount = test_game.coins;
    int expectedCoinCount = 8;
    if (assertTrue(coinCount == expectedCoinCount) && isSame(preStateCoins + 4, coinCount))
        printf(" Test 2: PASSED ** COIN COUNT is %d; Expected COIN COUNT is %d \n ", coinCount, expectedCoinCount);
    else
        printf(" Test 2: FAILED ** COIN COUNT is %d; Expected COIN COUNT is %d \n ", coinCount, expectedCoinCount);

    //Test 4: choice1 = 1 | player: -1 estate | 
    

    // printf("Estate count: %d \n", test_game.supplyCount[i]);

    //Test 5: choice1 = 1 |game state : +1 estate |


    // ** Choice 2 Testing
    //Test 6
                 return 0;
}