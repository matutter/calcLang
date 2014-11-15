// parse calc 
// mathew utter 
// 11/12/2014 
#include "definecalc.h"
#include <queue>
/********************
// after-thought... this is the same language as yours, just closer to BNF

// the language below is like what I was trying to explain in class. 
// we can remove the terms F and G by moving the grammar for value types farther away from the expression filter...
// that allows us to evaluate lower order things as a product of lower order things as a product of values or other expressions...
// language from http://web.cse.ohio-state.edu/software/2231/web-sw2/extras/slides/27.Recursive-Descent-Parsing.pdf
	lang --> expr
	expr --> term {add-op term}        // {left associative}
	term --> factor {mult-op factor}   // {commutative} repeat and reduce call stack
	factor --> ( expr ) | number
	add-op --> + | -
	mult-op --> * | / | %
	number --> [0-9]
*********************/

//#define PARSEDEBUG

#include <iostream>
using namespace std;
namespace TermCalc
{
	class Parser
	{	
	private:
		_LVAL *ret_val;
		//size_t sp;
		//size_t limit;
		//size_t CYCLE;
	public:
		Parser() {
			//this->CYCLE = 0;
		}
		bool low_order_op(Symbol s)
		{
			return s == plus || s == sub;
		}
		bool high_order_op(Symbol s)
		{
			return s == div || s == mult || s == mod;
		}
		_LVAL factor(queue<lambda> *ts)
		{
			_LVAL val = -1;
			switch( ts->front().type )
			{
				case lparen:
					ts->pop();
					val = expr(ts);
					ts->pop();
				break;
				case TermCalc::val:
					val = ts->front().val;
					ts->pop();
			}
			return val; 
		}
		_LVAL term(queue<lambda> *ts)
		{
			_LVAL val = factor(ts);
			while( high_order_op( ts->front().type ) ){
				lambda s = ts->front();
				ts->pop();		
				val = s.func(val,factor(ts));
			}
			return val;
		}
		_LVAL expr(queue<lambda> *ts)
		{
			_LVAL val = term(ts);
			while(  low_order_op( ts->front().type ) ) {
				lambda s = ts->front();
				ts->pop();
				val = s.func(val,term(ts));
			}
			return val;
		}
		_LVAL lang(queue<lambda> *ts)
		{
			return expr(ts);
		}
		Parser& parse(queue<lambda> *syml)
		{
			this->ret_val = new RETURN_TYPE;
			*ret_val = lang( syml );
			if( !syml->empty() )
			{
				throw EXPR_ERR;
			}
			return *this;
		}
		/* clean up */
		void dispose() {}
		Parser& eval(RETURN_TYPE * ret)
		{
			*ret = *ret_val;
			return *this;
		}
	};
}