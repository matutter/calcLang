// parse calc 
// mathew utter 
// 11/12/2014 
#include "definecalc.h"
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
		RETURN_TYPE *ret_val;
		lambda ** syml;
		size_t sp;
		size_t limit;
		size_t CYCLE;
	public:
		Parser() {
			this->CYCLE = 0;
		}

		bool getsym() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tgetsym" << endl;
			#endif
			if( sp < limit ) return ++sp;
			return false;
		}

		bool remaining() {
			return sp != limit;
		}

		bool accept( Symbol s ) {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\taccept" << code_to_type(s) << endl;
			#endif
			return syml[sp]->type == s;
		}
		bool expect( Symbol s ) {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\texpect " << code_to_type(s) << endl;
			#endif
			if( syml[sp+1]->type == s ) return true;
			cout << "missing\t" << code_to_type(s) << endl;
			return false;
		}
		void terminate() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tterminate " << endl;
			#endif
		};
		lambda H() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tH" << endl;
			#endif
			if( accept( val ) )
			{
				RETURN_TYPE val = syml[sp]->val;
				getsym();
			}
			else if( accept( lparen ) )
			{
				getsym();
				E();
				expect( rparen );
			}
		};
		lambda I() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tI" << endl;
			#endif
			lambda *l = syml[sp];
			if( accept(mult) )
			{
				if( !getsym() ) throw I_ERR;
				H();
				if(remaining()) I();
			}
			else if( accept(div) )
			{
				if( !getsym() ) throw I_ERR;
				H();
				if(remaining()) I();
			}
			else if( accept( mod ) )
			{
				if( !getsym() ) throw I_ERR;
				H();
				if(remaining()) I();			
			}
			else
			{
				accept(l->type);
				getsym();
			}
		};
		lambda F() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE  << code_to_type( syml[sp]->type ) << "\tF " << endl;
			#endif
			H();
			if(remaining()) I();
		}
		lambda G() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tG " << endl;
			#endif
			lambda *l = syml[sp];
			if( accept( plus ) )
			{
				if( !getsym() ) throw G_ERR;
				F();
				if(remaining()) G();
			}
			else if( accept( sub ) )
			{
				if( !getsym() ) throw G_ERR;
				F();
				if(remaining()) G();
			}
			else
			{
				accept(l->type);
				getsym();
			}
		}

		void E()
		{
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tE " << endl;
			#endif
			F();
			if(remaining()) G();
		}

		void L() {
			#ifdef PARSEDEBUG
				cout << ++CYCLE << code_to_type( syml[sp]->type ) << "\tL " << endl;
			#endif
			//getsym();
			E();
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
			this->syml = syml;
			this->sp = 0;
			this->limit = size;
			L();
			#ifdef PARSEDEBUG
				cout <<  sp << '/' << size << (sp==size?"":" FAIL") << endl;
			#endif
			return *this;
		}

		void dispose()
		{
			delete( ret_val );
			delete( syml );
			sp = 0;
		}

		Parser& eval(RETURN_TYPE * ret)
		{
			*ret = *ret_val;
			return *this;
		}

	};

}