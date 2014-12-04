#include "definecalc.hpp"
#include "terminalcalc.hpp"
#include "lexcalc.hpp"

/* lemon files */
#include "parser.h"
#include "parser.c"
using namespace std;
using namespace TermCalc;

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 12; ++i) cout << "#*#";
	cout << endl << "| Spaces are allowed in expressions.\n"
					"| Press 'Enter' to calculate.\n"
					"| Press 'q' twice to quit.\n" << endl;

	//string s = "1*2+1 * (9 + ((8+1) * 7)) + 2 * (3  + 2) * 2"; // 94
	//string s = "snack  = ((1+8%7)+5)";
	string s = "";
	Terminal    term( &s );
	Lexer       lex( &s );

	lambda null = { END, END, };
	while( term.capture() ) {
		vector<lambda> sym;
		try {
			if( lex.analyze( sym ) ) {
				void* pParser = ParseAlloc (malloc);
				for (std::vector<lambda>::iterator i = sym.begin(); i != sym.end(); ++i)
					Parse(pParser, i->type, *i);  
				Parse(pParser, null.type, null);
				ParseFree(pParser, free ); 
			}
		} catch( ErrorCodes e ) {
			cout << endl << "Error: expected " << error_from_code( e ) << endl;
		}
		s.clear();
	}
	s.clear();
	cout<<"\n\n\n";
	return 0;
}