#include "definecalc.hpp"
#include "terminalcalc.hpp"
//#include "parsecalc.hpp"
#include "lexcalc.hpp"

/* lemon files */
#include "parser.h"
#include "parser.c"
using namespace std;
using namespace TermCalc;

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 36; ++i) cout << '#';
	cout << endl << "| Spaces are allowed in expressions.\n| Press 'Enter' to calculate.\n| Press 'q' to quit.\n" << endl;

	//string s = "1*2+1 * (9 + ((8+1) * 7)) + 2 * (3  + 2) * 2"; // 94
	string s = "((1+1*3)/2)";
	//string s = "";
	RETURN_TYPE ret;
	Terminal    term( &s );
	Lexer       lex( &s );
	//Parser      parser;

	/*while( term.capture() )*/ {
		/*queue<lambda> sym;*/
		vector<lambda> sym;
		lambda null = { END, END, _UNREACHABLE_func, };
		try {
			if( lex.analyze( sym ) ) {
				//parser.parse(&sym).eval(&ret).dispose();
				void* pParser = ParseAlloc (malloc);
				for (std::vector<lambda>::iterator i = sym.begin(); i != sym.end(); ++i)
					Parse(pParser, i->type, *i);  
				Parse(pParser, null.type, null);
				ParseFree(pParser, free ); 
				//cout << " = " << ret << endl;
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