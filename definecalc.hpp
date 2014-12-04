#ifndef _definecalc_hpp
#define _definecalc_hpp

#include <queue>
#include <cstdio>
#include <string>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>
#include "parser.h"
#include <map>

std::map<std::string, int> id_map;
std::map<int, std::string> rev_id_map;
std::map<int,int>    val_map;

#ifndef END 
#define END 98
#endif
#ifndef IDENT
#define IDENT 99
#endif

#define _LVAL int
#define RETURN_TYPE _LVAL
//#define PARSEDEBUG
namespace TermCalc
{

	typedef enum {
		H_ERR, I_ERR, TERM_ERR, VAL_ERR, G_ERR, EXPR_ERR, L_ERR, LPAR_ERR, NOIDENT
	} ErrorCodes;
	typedef struct {
		/*Symbol*/int type;
		_LVAL val;
		_LVAL (*func)(_LVAL, _LVAL);
	} lambda;
	int id = 0;
	int GetCreateIdent(std::string s) {
		if( id_map.find(s) == id_map.end() ) {
			id_map[s]      = id;
			rev_id_map[id] = s;
			val_map[id]    = 0;
			id++;
		}
		return id_map[s];
	}

	bool validID(lambda l) {
		if( l.type != IDENT ) throw EXPR_ERR;
		if( rev_id_map.find(l.val) == rev_id_map.end()  ) throw NOIDENT;
		return true;
	}

	_LVAL ValFromID(lambda l) {
		validID(l);
		return val_map[l.val];
	}

	void IdentSet(lambda l, _LVAL b) {
		validID(l);
		val_map[l.val] = b;
	}

	/* these used to be lower case */
	typedef enum {
		//LPAREN, RPAREN, PLUS, SUB, MULT, MOD, DIV, VAL
	} Symbol;

	inline int/*Symbol*/ TYPECODE(char x)
	{
		switch(x) 				
		{	case '(': return LPAREN; 
			case ')': return RPAREN; 
			case '+': return PLUS; 
			case '-': return SUB; 
			case '*': return MULT; 
			case '%': return MOD; 
			case '/': return DIV;
			case END: return END;
			case IDENT: return IDENT;
			case '=': return EQ;
			default : return VAL; 
		}
	}

	std::string code_to_type( /*Symbol*/int x )
	{
		switch(x) 				
		{	case LPAREN : return "_LPAREN"; 
			case RPAREN : return "_RPAREN"; 
			case PLUS 	: return "_PLUS"; 
			case SUB 	: return "_SUB"; 
			case MULT 	: return "_MULT"; 
			case MOD 	: return "_MOD"; 
			case DIV 	: return "_DIV"; 
			case VAL 	: return "_VAL_t";
			case END    : return "_END_t";
			case IDENT  : return "_IDENT_t;";
			case EQ     : return "_eq";
		}		
	}


	std::string error_from_code( int x )
	{
		switch(x) 				
		{	case H_ERR : return "h argument"; 
			case I_ERR : return "i argument"; 
			case TERM_ERR 	: return "termination argument"; 
			case VAL_ERR 	: return "VALue"; 
			case G_ERR 	: return "right argument"; 
			case EXPR_ERR 	: return "expression"; 
			case L_ERR 	: return "language"; 
			case LPAR_ERR 	: return "unmet parenthesis"; 
			case NOIDENT  : return "Unknown identifier";
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

	std::string findIdent( std::string::iterator *c ) {
		std::string s = "";
		while( **c != 0x0 && (isdigit(**c) || isalpha(**c)) ) {
			s+= **c;
			(*c)++;
		}
		return s;
	}



	inline std::ostream &operator<<(std::ostream &out, const lambda &l) {
		if( l.type==VAL )
			out << code_to_type(l.type) << "\t" << l.val;
		else
			out << code_to_type(l.type) << "\t" << code_to_type(l.type);
		return out;
	}

	inline _LVAL _UNREACHABLE_func(_LVAL a, _LVAL b) {
		#ifdef PARSEDEBUG
			std::cout << "_UNREACHABLE_func" << std::endl;
		#endif
		return 0;
	}
	TermCalc::lambda _rparen = {
		TYPECODE( ')' ),
		0,
		_UNREACHABLE_func,
	};
	TermCalc::lambda _lparen = {
		TYPECODE( '(' ),
		0,
		_UNREACHABLE_func,
	};


	inline _LVAL _PLUS_func(_LVAL a, _LVAL b) {
		return a + b;
	}
	TermCalc::lambda _plus = {
		TYPECODE( '+' ),
		0,
		_PLUS_func,
	};
	inline _LVAL _MULT_func(_LVAL a, _LVAL b) {
		return a * b;
	}
	TermCalc::lambda _mult = {
		TYPECODE( '*' ),
		0,
		_MULT_func,
	};
	inline _LVAL _DIV_func(_LVAL a, _LVAL b) { 
			return a / b;
		}
	TermCalc::lambda _div = {
		TYPECODE( '/' ),
		0,
		_DIV_func,
	};
	inline _LVAL _SUB_func(_LVAL  a, _LVAL  b) {
		return a - b;
	}
	TermCalc::lambda _sub = {
		TYPECODE( '-' ),
		0,
		_SUB_func,
	};
	inline _LVAL _MOD_func(_LVAL  a, _LVAL  b) {
		return a % b;
	}
	TermCalc::lambda _mod = {
		TYPECODE( '%' ),
		0,
		_MOD_func,
	};	
	TermCalc::lambda _eq = {
		TYPECODE( '=' ),
		0,
		_MOD_func,
	};

}
#endif