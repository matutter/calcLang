#ifndef _lexcalc_hpp
#define _lexcalc_hpp
#include "definecalc.hpp"
namespace TermCalc
{
	class Lexer
	{
	public:
		std::string * buffer;
		Lexer(std::string * buf)
		{
			this->buffer = buf;
		}
		int analyze(std::queue<lambda> *symbols)
		{
			std::string::iterator it = this->buffer->begin();
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
			std::cout << std::endl;
			for (int i = 0; i < pos; ++i)
				std::cout << " ";
			std::cout << "^" << std::endl;
			std::cout << "ERROR col " << pos << std::endl;
			return 0;
		}
	};
}
#endif