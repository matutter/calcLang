#include "terminalcalc.h"
#include "parsecalc.h"
#include "lexcalc.h"
#include "definecalc.h"

#include <iostream>

using namespace std;




int main(int argc, char const *argv[])
{
	
	string s = "9 * 2 + 8 * 2";
	RETURN_TYPE ret;
	TermCalc::Terminal 	term( &s );
	TermCalc::Lexer 	lex( &s );
	TermCalc::Parser 	parser;

	//while( term.capture() ) {
		TermCalc::lambda ** sym = new TermCalc::lambda*[ s.size() ];
		size_t size = 0;
		
		try {
			if( lex.analyze( sym, &size ) )
				parser.parse(sym, size).eval(&ret).dispose();
		} catch( TermCalc::ErrorCodes e ) {
			cout << endl << "Error: expected " << TermCalc::error_from_code( e ) << endl;
		}
		
		s.clear();
		
	//}


	s.clear();

	return 0;
}