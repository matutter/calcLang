#include "definecalc.h"

#include <iostream>

using namespace std;

namespace TermCalc
{

	class Lexer
	{
	public:
		string * buffer;
		Lexer(string * buf)
		{
			this->buffer = buf;
		}
		int analyze(lambda ** symbols, size_t * l)
		{
			//symbols = new lambda*[ this->buffer->size() ];
			string::iterator it = this->buffer->begin();
			while( it != this->buffer->end() )
			switch( *it )
			{
				case '(':
					symbols[(*l)++] = &TermCalc::_lparen;
					it++;
				break;
				case ')':
					symbols[(*l)++] = &TermCalc::_rparen;
					it++;
				break;
				case '+':
					symbols[(*l)++] = &TermCalc::_plus;
					it++;
				break;
				case '-':
					symbols[(*l)++] = &TermCalc::_sub;
					it++;
				break;
				case '*':
					symbols[(*l)++] = &TermCalc::_mult;
					it++;
				break;				
				case '%':
					symbols[(*l)++] = &TermCalc::_mod;
					it++;
				break;
				case '/':
					symbols[(*l)++] = &TermCalc::_div;
					it++;
				break;
				default:
					if( isdigit( *it ) ) {
						symbols[*l] = new TermCalc::lambda;
						symbols[*l]->type = TYPECODE(0x0);
						symbols[*l]->val = TermCalc::atoi(&it);
						(*l)++;
					}
					else if( isspace(*it) )
						it++;
					else return ERR( it - this->buffer->begin() );
			}
			return 1;
		}
	private:
		int ERR(int pos) {
			cout << endl;
			for (int i = 0; i < pos; ++i)
				cout << " ";
			cout << "^" << endl;
			cout << "ERROR col " << pos << endl;
			return 0;
		}
	};


}