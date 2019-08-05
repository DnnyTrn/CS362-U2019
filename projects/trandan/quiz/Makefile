quiz: testme.c
	gcc -o quiz testme.c -coverage -fpic -lm -std=c99

testme: quiz
	- ./quiz
	gcov testme.c -b -f

clean: 
	rm -f *.o  *.gcov *.gcda *.gcno *.so *.out quiz
