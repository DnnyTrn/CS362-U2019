// to compile this file
// gcc -o cardtest4 dominion.c rngs.c cardtest4.c

#include "dominion.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "getWinners()"

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
  
    int numPlayers = 4, i, j, k, testRun = 100;
    int players[4];

    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, 1, &g);
    


    // g.discard[1][0] = province;
    // g.deck[1][0] = province;
    // g.hand[1][0] = province;
    // g.handCount[1] = 1;
    // g.discardCount[1] = 1;
    //  printf(" g.discard[1][0] %d \n", g.discard[1][0]);
    // printf(" %d %d %d \n", g.handCount[1], g.discardCount[1], g.deckCount[1]);
    // getWinners(players, &g);

    // alternate winners to test getWinners
    // for ( i = 0; i < numPlayers; i++)
    // {
        
    //     getWinners(players, &g);
    //     g.deck[i][0] = province;
    //     printf(" player: %d \n", i );
    //     ASSERT(players[i] == 1, "error");
    // }

    // // print players array
    printf("Test 1: winner return \n");

    for ( i = 0; i < numPlayers; i++)
    {
        // printf(" %d score %d \n", i, players[i] );

        g.discard[i][0] = province;
        g.deck[i][0] = province;
        g.hand[i][0] = province;
        g.handCount[i] = 1;
        g.discardCount[i] = 1;
        getWinners(players, &g);

        ASSERT(players[i] == 1, "Test 1: function failed to set winning players ");

        g.discard[i][0] = curse;
        g.deck[i][0] = curse;
        g.hand[i][0] = curse;
        getWinners(players, &g);

        ASSERT(players[i] == 0, "Test 2: function failed to set losing players");
    }

    for (i = 0; i < numPlayers; i++)
    {


        printf(" player: %d \n", players[i]);

    }

    // printf("Test 2: Testing for correct player turn\n");
    // printf("Test 3: Testing for correct player variables intialization\n");
    for (i = 0; i < testRun; i++)
    {
        for (j = 0; j < numPlayers; j++)
        {
        }
    }
    printf("** Card test 4 concluded. **\n");
    return 0;
}
