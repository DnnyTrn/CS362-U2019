// to compile this file
// gcc -o randomtestcard1 dominion.c rngs.c randomtestcard1.c -Wall -fpic -coverage -lm -std=c99

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "baron"

int checkPlayBaron(struct gameState* post, int currentPlayer, int choice1){
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    
    playBaron(post, choice1, currentPlayer);

    return 0;
}
int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 4, i, j, n, p, choice1 = 1, testRun = 1000;
    int currentPlayer = 0;
    srand(time(0));

    for (n = 0; n < 900; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&g)[i] = rand() % 256;
        }

        choice1 = rand() % 2;
        currentPlayer = rand() % MAX_PLAYERS;
        g.supplyCount[estate] = rand() % 13;
        g.discardCount[currentPlayer] = rand() % MAX_DECK;
        g.handCount[currentPlayer] = rand() % 10;
        g.hand[currentPlayer][rand() % 10] = estate;
        printf(" SUPPLY COUNT IS %d \n", g.supplyCount[estate] = rand() % 2);
        checkPlayBaron(&g, currentPlayer, choice1);
    }

    printf("** Random test card 1 concluded. **\n");
    return 0;
}