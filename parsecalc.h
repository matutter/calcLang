// parse calc 
// mathew utter 
// 11/12/2014 
#include "definecalc.h"
#include <vector>
/********************
	L --> E
	E --> F G
	F --> H I
	G --> + F G
	G --> - F G
	G -->
	H --> integer
	H --> ( E )
	I --> * H I
	I --> / H I
	I --> % H I
	I --> 
*********************/

#define PARSEDEBUG

#include <iostream>
using namespace std;
namespace TermCalc
{
	class Parser
	{	
	private:
		_LVAL *ret_val;
		lambda * syml;
		lambda ** symbols;
		vector<lambda> op;
		size_t sp;
		size_t limit;
		size_t CYCLE;
	public:
		Parser() {
			this->CYCLE = 0;
		}
		
		_LVAL epsilon()
		{
			//cout << "*";
		}

		void consume( Symbol s, int frame )
		{
			if( syml->type == s )
			{
				cout << frame;
				while( frame-- ) cout << " ";
				cout << "consume " << code_to_type(s) << endl;
				op.push_back( *syml );
				if( --limit )
					syml = symbols[++sp];
			}
		}

		void H(int frame)
		{
			switch( syml->type )
			{
				case val:
					consume( val, frame );
				break;
				case lparen:
					consume( lparen, frame );
					E(frame+1);
					consume( rparen, frame );
			}
		}
		void I(int frame)
		{
			switch( syml->type )
			{
				case mult:
				case div:
				case mod:
					consume( syml->type, frame );
					H(frame);
					I(frame+1);
					break;
				default:
					epsilon();
			}
		}
		void G(int frame)
		{
			switch( syml->type )
			{
				case plus:
				case sub:
					consume( syml->type, frame );
					F(frame+1);
					G(frame+1);
					break;
				default:
					epsilon();
			}
		}
		void F(int frame)
		{
			H(frame+1);
			I(frame+1);
		}
		void E(int frame)
		{
			F(frame+1);
			G(frame+1);
		}
		void L(int frame)
		{
			E(frame+1);
		}


		Parser& parse(lambda ** syml, size_t size)
		{
			#ifdef PARSEDEBUG
				cout << "\nparsing" << endl;
				for (int i = 0; i < size; ++i)
					cout << *syml[i] << endl;
				cout << "__________________" << endl;
			#endif
			this->ret_val = new RETURN_TYPE;
			this->syml = syml[0];
			this->symbols = syml;
			this->sp = 0;
			this->limit = size;
			int frame = 0;
			L( frame );
			#ifdef PARSEDEBUG
				cout <<  sp+1 << '/' << size << " steps" << endl;
			#endif
			return *this;
		}

		void dispose()
		{
			delete( ret_val );
			//delete( syml );
			sp = 0;
		}

		Parser& eval(RETURN_TYPE * ret)
		{
			*ret = *ret_val;
			return *this;
		}

	};

}