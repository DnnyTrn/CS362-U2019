// to compile this file
// gcc -o randomtestcard2 dominion.c rngs.c randomtestcard2.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "minion"

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int numPlayers = 4, i, j, testRun = 1000;
    int currentPlayer = 0;
    srand(time(0));

   

    printf("** Random test card 2 concluded. **\n");
    return 0;
}