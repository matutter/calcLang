// parse calc 
// mathew utter 
// 11/12/2014 
#include "definecalc.h"
/**********************
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

		void getsym()
		{
			sp++;
		}

		void expression()
		{

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