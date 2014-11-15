// parse calc 
// mathew utter 
// 11/12/2014
#ifndef _parsecalc_hpp
#define _parsecalc_hpp
#include "definecalc.hpp"
/********************
// **after-thought... this is the same language as yours, just closer to BNF**
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
namespace TermCalc
{
	class Parser
	{	
	private:
		_LVAL *ret_val;
	public:
		Parser() {}
		bool low_order_op(Symbol s)
		{
			return s == plus || s == sub;
		}
		bool high_order_op(Symbol s)
		{
			return s == div || s == mult || s == mod;
		}
		_LVAL factor(std::queue<lambda> *ts)
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
		_LVAL term(std::queue<lambda> *ts)
		{
			_LVAL val = factor(ts);
			while( high_order_op( ts->front().type ) ) {
				lambda s = ts->front();
				ts->pop();		
				val = s.func(val,factor(ts));
			}
			return val;
		}
		_LVAL expr(std::queue<lambda> *ts)
		{
			_LVAL val = term(ts);
			while(  low_order_op( ts->front().type ) ) {
				lambda s = ts->front();
				ts->pop();
				val = s.func(val,term(ts));
			}
			return val;
		}
		_LVAL lang(std::queue<lambda> *ts)
		{
			return expr(ts);
		}
		Parser& parse(std::queue<lambda> *syml)
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
		void dispose() { /*nothing to clean in here*/ }
		Parser& eval(RETURN_TYPE * ret)
		{
			*ret = *ret_val;
			return *this;
		}
	};
}
#endif