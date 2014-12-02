TermCalc_mat.o: maincalc.cpp
	lemon parser.y
	g++ maincalc.cpp -o TermCalc_mat.o

TEST: maincalc.cpp
	lemon parser.y
	g++ maincalc.cpp -o TermCalc_test.o
	./TermCalc_test.o

DEBUG: maincalc.cpp
	lemon parser.y
	g++ -Wall -Wextra -ggdb -O0 -Wunreachable-code maincalc.cpp -o TermCalc_DBG.o