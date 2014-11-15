#include "definecalc.hpp"
#include "terminalcalc.hpp"
#include "parsecalc.hpp"
#include "lexcalc.hpp"

using namespace std;
using namespace TermCalc;

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 36; ++i) cout << '#';
	cout << endl << "| Spaces are allowed in expressions.\n| Press 'Enter' to calculate.\n| Press 'q' to quit.\n" << endl;

	//string s = "1*2+1 * (9 + ((8+1) * 7)) + 2 * (3  + 2) * 2"; // 94
	string s = "";
	RETURN_TYPE ret;
	Terminal    term( &s );
	Lexer       lex( &s );
	Parser      parser;

	while( term.capture() ) {
		queue<lambda> * sym = new queue<lambda>;
		try {
			if( lex.analyze( sym ) ) {
				parser.parse(sym).eval(&ret).dispose();
				cout << " = " << ret << endl;
			}
		} catch( ErrorCodes e ) {
			cout << endl << "Error: expected " << error_from_code( e ) << endl;
		}
		delete( sym );
		s.clear();
	}
	s.clear();

	return 0;
}