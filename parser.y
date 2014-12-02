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
   
%type ex      {_LVAL}
%type term    {_LVAL}
%type fact    {_LVAL}


%left PLUS SUB.
%left MULT DIV MOD.

%syntax_error { throw EXPR_ERR; }


/*lang ::= ex(L). { cout << "\n\n = " << L  << endl << flush; }*/
/* THIS LANGUAGE IS NONSENSE */
/*math ::= l(R).  {  cout << R << endl; }
l(R) ::= e(A).				{ R.val = A.val; }
e(R) ::= f(A) g(B).			{ R.val = A.func(A.val,B.val); }
f(R) ::= h(A) i(B). 		{ R.val = A.func(A.val,B.val); }
g(R) ::= PLUS(O) f(A) g(B). { if( B.type == END ) R.func = O.func; R.val = A.val; }
g(R) ::= SUB(O)  f(A) g(B). { if( B.type == END ) R.func = O.func; R.val = A.val; }
h(R) ::= VAL(A). 			{ R.val  = A.val; R.type = VAL; }
h(R) ::= LPAREN e(A) RPAREN.{ R.val  = A.val; }
h(R) ::= END.				{ R.type = END; }
i(R) ::= MULT(O) H(A) I(B). { if( B.type == END ) R.func = O.func; R.val = A.val; }
i(R) ::= DIV(O)  H(A) I(B). { if( B.type == END ) R.func = O.func; R.val = A.val; }
i(R) ::= MOD(O)  H(A) I(B). { if( B.type == END ) R.func = O.func; R.val = A.val; }
i(R) ::= END.				{ R.type = END; }*/

ex(L) ::= terma(A).						{ L = A; }
ex(L) ::= terma(A) sum(O) termb(B).		{ L = O.func(A, B); }

sum(L) ::=	PLUS(A).					{ L = A; }
sum(L) ::=	SUB(A).						{ L = A; }

term(L) ::= fact(A).					{ L = A; }
term(L) ::= fact(A) prod(O) fact(B).	{ L = O.func(A, B); }

prod(L) ::= MULT(A).					{ L = A; }
prod(L) ::= DIV(A).						{ L = A; }
prod(L) ::= MOD(A).						{ L = A; }

fact(L) ::= VAL(A). 					{ L = A.val; }
fact(L) ::= LPAREN ex(A) RPAREN.		{ L = A; cout << "(ex("<<A<<"))\n"; }