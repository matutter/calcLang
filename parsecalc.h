// parse calc 
// mathew utter 
// 11/12/2014 
#include "definecalc.h"
/**********************
	L --> E *
	E --> L R*
	L --> H I*
	R --> + L R*
	R --> - L R*
	R -->*
	H --> integer
	H --> ( E )
	I --> * H I
	I --> / H I
	I --> % H I
	I --> 
**********************/
#include <iostream>
using namespace std;
namespace TermCalc
{
	class Parser
	{	
	private:
		RETURN_TYPE *ret_val;
		lambda ** syml;
		lambda * sp;
	public:
		Parser(){}

		void getsym() { sp++; }

		void harg() {
			if( accept( val ) )
			{
				getsym();
			}
			else if( accept( lparen ) )
			{
				getsym();
				expression();
				expect( rparen );
			}
		};
		void iarg() {
			
		};
		bool accept( Symbol s ) {
			return sp->type == s;
		};
		bool expect( Symbol s ) {
			if( sp->type == s ) return true;
			cout << "missing" << code_to_type(s) << endl;
			return false;
		}
		void terminate(){};
		void larg() {
			harg();
			iarg();
		}
		void rarg() {
			if( accept( plus ) )
			{
				getsym();
				larg();
				rarg();
			}
			else if( accept( sub ) )
			{
				getsym();
				larg();
				rarg();
			}	
			else terminate();
		}

		void expression()
		{
			larg();
			rarg();
		}

		void lang() {
			//getsym();
			expression();
		}


		Parser& parse(lambda ** syml)
		{
			cout << "\nparsing" << endl;
			this->ret_val = new RETURN_TYPE;
			this->syml = syml;
			this->sp = this->syml[0];
			lang();
			return *this;
		}

		void dispose()
		{
			delete( ret_val );
			delete( syml );
			delete( sp );
		}

		Parser& eval(RETURN_TYPE * ret)
		{
			*ret = *ret_val;
			return *this;
		}

	};

}