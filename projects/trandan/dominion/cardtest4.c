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
  
    int numPlayers = 4, i;
    int players[4];

    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    initializeGame(numPlayers, cards, 1, &g);
    

    for ( i = 0; i < numPlayers; i++)
    {
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

    printf("** Card test 4 concluded. **\n");
    return 0;
}
