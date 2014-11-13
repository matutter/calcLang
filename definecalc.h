#ifndef _definecalc_h
#define _definecalc_h

#include <stdint.h>
#define _LVAL uint32_t
#define RETURN_TYPE _LVAL

namespace TermCalc
{
	typedef enum {
		lparen, rparen, plus, sub, mult, mod, div, val
	} Symbol;


	inline Symbol TYPECODE(char x)
	{
		switch(x) 				
		{	case '(': return lparen; 
			case ')': return rparen; 
			case '+': return plus; 
			case '-': return sub; 
			case '*': return mult; 
			case '%': return mod; 
			case '/': return div; 
			default : return val; 
		}
	}

	string code_to_type( Symbol x )
	{
		switch(x) 				
		{	case lparen : return "_lparen"; 
			case rparen : return "_rparen"; 
			case plus 	: return "_plus"; 
			case sub 	: return "_sub"; 
			case mult 	: return "_mult"; 
			case mod 	: return "_mod"; 
			case div 	: return "_div"; 
			case val 	: return "_value_t"; 
		}		
	}

	_LVAL atoi( string::iterator * c ) {
		_LVAL val = 0;
		while( **c != 0x0 && isdigit(**c) ) {
			val *= 10;
			val += **c - '0';
			(*c)++;
		}
		return val;
	}

	struct lambda {
		Symbol type;
		_LVAL val;
		_LVAL (*func)(lambda*, lambda*);
	};

	inline ostream &operator<<(std::ostream &out, const lambda &l) {
		if( l.type==val )
			out << code_to_type(l.type) << " " << l.val;
		else
			out << code_to_type(l.type) << " " << (char)l.type;
		return out;
	}

	TermCalc::lambda _rparen = {
		TYPECODE( ')' ),
	};
	TermCalc::lambda _lparen = {
		TYPECODE( '(' ),
	};

	inline _LVAL _plus_func(lambda * a, lambda * b) { return a->val + b->val; }
	TermCalc::lambda _plus = {
		TYPECODE( '+' ),
		0,
		_plus_func,
	};
	inline _LVAL _mult_func(lambda * a, lambda * b) { return a->val * b->val; }
	TermCalc::lambda _mult = {
		TYPECODE( '*' ),
		0,
		_mult_func,
	};
	inline _LVAL _div_func(lambda * a, lambda * b) { return a->val / b->val; }
	TermCalc::lambda _div = {
		TYPECODE( '/' ),
		0,
		_div_func,
	};
	inline _LVAL _sub_func(lambda * a, lambda * b) { return a->val - b->val; }
	TermCalc::lambda _sub = {
		TYPECODE( '-' ),
		0,
		_sub_func,
	};
	inline _LVAL _mod_func(lambda * a, lambda * b) { return a->val % b->val; }
	TermCalc::lambda _mod = {
		TYPECODE( '%' ),
		0,
		_mod_func,
	};	


}
#endif