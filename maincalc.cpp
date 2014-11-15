#include "terminalcalc.h"
#include "parsecalc.h"
#include "lexcalc.h"
#include "definecalc.h"

#include <queue>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 36; ++i) cout << '#';
	cout << endl << "| Spaces are allowed in expressions.\n| Press 'Enter' to calculate.\n| Press 'q' to quit.\n" << endl;

	//string s = "1*2+1 * (9 + ((8+1) * 7)) + 2 * (3  + 2) * 2"; // 94
	string s = "";
	RETURN_TYPE ret;
	TermCalc::Terminal 	term( &s );
	TermCalc::Lexer 	lex( &s );
	TermCalc::Parser 	parser;

	while( term.capture() ) {
		queue<TermCalc::lambda> * sym = new queue<TermCalc::lambda>;
		try {
			if( lex.analyze( sym ) ) {
				parser.parse(sym).eval(&ret).dispose();
				cout << " = " << ret << endl;
			}
		} catch( TermCalc::ErrorCodes e ) {
			cout << endl << "Error: expected " << TermCalc::error_from_code( e ) << endl;
		}
		delete( sym );
		s.clear();
	}
	s.clear();

	return 0;
}