#include "terminalcalc.h"
#include "parsecalc.h"
#include "lexcalc.h"
#include "definecalc.h"

#include <iostream>

using namespace std;




int main(int argc, char const *argv[])
{
	
	string s;
	RETURN_TYPE ret;
	TermCalc::Terminal 	term( &s );
	TermCalc::Lexer 	lex( &s );
	TermCalc::Parser 	parser;

	while( term.capture() ) {
		TermCalc::lambda ** sym = new TermCalc::lambda*[ s.size() ];
		size_t size = 0;
		
		if( lex.analyze( sym, &size ) )
			parser.parse(sym).eval(&ret).dispose();
		
		
		s.clear();
		delete(sym);
	}


	s.clear();

	return 0;
}