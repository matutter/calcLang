%include {   
#include <iostream>  
#include <cstdlib>
#include <assert.h>
#include "definecalc.hpp"
#include <stdint.h>
using namespace TermCalc;
using namespace std;
#define PARSERDEBUG

}  

%token_type   {lambda}
%default_type {lambda}

%type math    {_LVAL}
%type num     {_LVAL}
%type ex      {_LVAL}
%type run      {_LVAL}
/*%type term    {_LVAL}
%type fact    {_LVAL}*/

%left PLUS SUB.
%left MULT DIV MOD.

%syntax_error { throw EXPR_ERR; }


lang ::= run END.               

run ::= IDENT(A) EQ ex(B).        { cout << " = " << B << endl; TermCalc::IdentSet(A,B); }
run ::= ex(A).                    { cout << " = " << A  << endl << flush;  }

ex(L) ::= math(A).                { L = A; }

math(L) ::= math(A) PLUS math(B). { L = A + B; }
math(L) ::= math(A) SUB  math(B). { L = A - B; }
math(L) ::= math(A) DIV  math(B). { L = A / B; }
math(L) ::= math(A) MULT math(B). { L = A * B; }
math(L) ::= math(A) MOD  math(B). { L = A % B; }

math(L) ::= num(A).               { L = A; }
num(L)  ::= VAL(A).               { L = A.val; }
num(L)  ::= IDENT(A).			  { L = TermCalc::ValFromID(A); }
num(L)  ::= LPAREN ex(A) RPAREN.  { L = A; }
