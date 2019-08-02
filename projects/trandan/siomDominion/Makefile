CFLAGS= -Wall -fpic -coverage -lm -std=c99

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

	./randomtestcard2 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

	./randomtestcard3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcov dominion.c -b -f >> randomtestresults.out 

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcov dominion.c -b -f >> randomtestresults.out 

randomtestcard3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	gcov dominion.c -b -f >> randomtestresults.out 

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestresults.out

unittest1: unittest1.c dominion.o
	gcc -o unittest1 dominion.c rngs.c unittest1.c -g $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

unittest2: unittest2.c dominion.o
	gcc -o unittest2 dominion.c rngs.c unittest2.c -g $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 
	
unittest3: unittest3.c dominion.o
	gcc -o unittest3 dominion.c rngs.c unittest3.c -g $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

unittest4: unittest4.c dominion.o
	gcc -o unittest4 dominion.c rngs.c unittest4.c -g $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 
	
unittest5: unittest5.c dominion.o
	gcc -o unittest5 dominion.c rngs.c unittest5.c -g $(CFLAGS)
	./unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c -g $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 

cardtest5: cardtest5.c dominion.o
	gcc -o cardtest5 dominion.c rngs.c cardtest5.c $(CFLAGS)
	./cardtest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out 