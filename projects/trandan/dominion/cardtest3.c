// to compile this file
// gcc -o cardtest3 dominion.c rngs.c cardtest3.c

#include "dominion.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ASSERT(expr, error) \
    ((expr) ||              \
     printf("Assertion failed: %s\n", error))

#define TESTCARD "endTurn()"

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// void printArray(int *arr, int n)
// {
//     for (size_t i = 0; i < n; i++)
//     {
//         printf(" index %d element %d \n", i, arr[i]);
//     }
// }

int main()
{
    printf("\n----------------- Testing : %s ----------------\n", TESTCARD);
    // initialization variables
    struct gameState g;
    int cards[10] = {ambassador, baron, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy};
    int numPlayers = 4, handCount = 5, i, j, k, testRun = 100;
    initializeGame(numPlayers, cards, 1, &g);

    printf("Test 1: Test to see if previous player’s hand is discarded after endTurn.\n");
    for (i = 0; i < testRun; i++)
    {
        for (j = 0; j < numPlayers; j++)
        {
            endTurn(&g);
            for (k = 0; k < handCount; k++)
                ASSERT(g.hand[j][k] == -1, "Test 1 failed: Previous player's hand was not discarded");
        }
    }


    
    printf("** Card test 3 concluded. **\n");
    return 0;
}
