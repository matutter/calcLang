#include "definecalc.h"

#include <iostream>
#include <queue>
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
		int analyze(queue<lambda> *symbols)
		{
			string::iterator it = this->buffer->begin();
			while( it != this->buffer->end() )
			switch( *it )
			{
				case '(':
					symbols->push( _lparen );
					it++;
				break;
				case ')':
					symbols->push( _rparen );
					it++;
				break;
				case '+':
					symbols->push( _plus );
					it++;
				break;
				case '-':
					symbols->push( _sub );
					it++;
				break;
				case '*':
					symbols->push( _mult );
					it++;
				break;				
				case '%':
					symbols->push( _mod );
					it++;
				break;
				case '/':
					symbols->push( _div );
					it++;
				break;
				default:
					if( isdigit( *it ) ) {
						lambda l;
						l.type = TYPECODE(0x0);
						l.val = atoi(&it);
						symbols->push(l);
					}
					else if( isspace(*it) )
						it++;
					else return ERR( it - this->buffer->begin() );
			}
			return symbols->size();
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