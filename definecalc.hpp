#ifndef _definecalc_hpp
#define _definecalc_hpp

#include <queue>
#include <cstdio>
#include <string>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>

#define _LVAL int32_t
#define RETURN_TYPE _LVAL
//#define PARSEDEBUG
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

	std::string code_to_type( Symbol x )
	{
		switch(x) 				
		{	case lparen : return "_lparen"; 
			case rparen : return "_rparen"; 
			case plus 	: return "_plus"; 
			case sub 	: return "_sub"; 
			case mult 	: return "_mult"; 
			case mod 	: return "_mod"; 
			case div 	: return "_div"; 
			case val 	: return "_val_t"; 
		}		
	}

	typedef enum {
		H_ERR, I_ERR, TERM_ERR, F_ERR, G_ERR, EXPR_ERR, L_ERR, LPAR_ERR
	} ErrorCodes;


	std::string error_from_code( int x )
	{
		switch(x) 				
		{	case H_ERR : return "h argument"; 
			case I_ERR : return "i argument"; 
			case TERM_ERR 	: return "termination argument"; 
			case F_ERR 	: return "left argument"; 
			case G_ERR 	: return "right argument"; 
			case EXPR_ERR 	: return "expression"; 
			case L_ERR 	: return "language"; 
			case LPAR_ERR 	: return "unmet parenthesis"; 
		}		
	}
	_LVAL atoi( std::string::iterator * c ) {
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
		_LVAL (*func)(_LVAL, _LVAL);
	};

	inline std::ostream &operator<<(std::ostream &out, const lambda &l) {
		if( l.type==val )
			out << code_to_type(l.type) << "\t" << l.val;
		else
			out << code_to_type(l.type) << "\t" << code_to_type(l.type);
		return out;
	}

	TermCalc::lambda _rparen = {
		TYPECODE( ')' ),
	};
	TermCalc::lambda _lparen = {
		TYPECODE( '(' ),
	};

	inline _LVAL _plus_func(_LVAL a, _LVAL b) {
		#ifdef PARSEDEBUG
			cout << "\t_plus_func " << a << '+' << b << endl;
		#endif
		return a + b;
	}
	TermCalc::lambda _plus = {
		TYPECODE( '+' ),
		0,
		_plus_func,
	};
	inline _LVAL _mult_func(_LVAL a, _LVAL b) {
		#ifdef PARSEDEBUG
			cout << "\t_mult_func " << a << '*' << b << endl;
		#endif
		return a * b;
	}
	TermCalc::lambda _mult = {
		TYPECODE( '*' ),
		0,
		_mult_func,
	};
	inline _LVAL _div_func(_LVAL a, _LVAL b) { return a / b; }
	TermCalc::lambda _div = {
		TYPECODE( '/' ),
		0,
		_div_func,
	};
	inline _LVAL _sub_func(_LVAL  a, _LVAL  b) { return a - b; }
	TermCalc::lambda _sub = {
		TYPECODE( '-' ),
		0,
		_sub_func,
	};
	inline _LVAL _mod_func(_LVAL  a, _LVAL  b) { return a % b; }
	TermCalc::lambda _mod = {
		TYPECODE( '%' ),
		0,
		_mod_func,
	};	


}
#endif