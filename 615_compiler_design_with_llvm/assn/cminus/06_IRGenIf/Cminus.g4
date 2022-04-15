/* Cminus.g4 */
/* by Allyn Shell */
/* February 2022 */
/* Modified by Sabbir Ahmed */
/* March 2022 */

grammar Cminus;

@parser::visitorpreinclude {
#include "LLVM_Util.h"
#include "Semantics.h"
}

@parser::visitordeclarations {
Semantics semantics;
}

// Lexical Analyzer Rules

IF: 'if';
ELSE: 'else';
WHILE: 'while';
RETURN: 'return';

INT: 'int';
VOID: 'void';

ADD: '+';
SUB: '-';
MULT: '*';
DIV: '/';
ASN: '=';

LB: '[';
RB: ']';
LP: '(';
RP: ')';

SEMICOLON: ';';
COMMA: ',';

LTE: '<=';
LT: '<';
GT: '>';
GTE: '>=';
EQ: '==';
NEQ: '!=';

// 1 or more letters
ID: LETTER+;
fragment LETTER: [A-Za-z];

// 1 or more digits
NUM: DIGIT+;
fragment DIGIT: [0-9];

// comment and whitespace tokens get skipped
COMMENT: ('/*' (.)*? '*/' | '//' ~('\r' | '\n')*) -> skip;
WS: [ \t\r\n]+ -> skip;

// Parser Rules

program: (var_declaration | fun_declaration)+ EOF;
var_declaration: INT ID (LB size = NUM RB)? SEMICOLON;
fun_declaration:
	fun_type_specifier ID LP (param (COMMA param)* | VOID) RP compound_stmt;
fun_type_specifier: INT | VOID;
param: INT ID (LB RB)?;
compound_stmt: '{' var_declaration* statement* '}';
statement:
	compound_stmt
	| selection_stmt
	| iteration_stmt
	| assignment_stmt
	| return_stmt
	| exp SEMICOLON
	| SEMICOLON;
selection_stmt:
	IF LP relational_exp RP then_cond = statement (
		ELSE else_cond = statement
	)?;
iteration_stmt: WHILE LP relational_exp RP statement;
assignment_stmt: ID (LB size = exp RB)? ASN exp SEMICOLON;
return_stmt: RETURN exp? SEMICOLON;
exp:
	exp multop exp					# mult_exp
	| exp addop exp					# add_exp
	| LP (exp | relational_exp) RP	# paren_exp
	| ID (LB size = exp RB)?		# val_exp
	| ID LP (exp (COMMA exp)*)? RP	# call_exp
	| NUM							# num_exp;
addop: ADD | SUB;
multop: MULT | DIV;
relational_exp: lhs = exp relop rhs = exp;
relop: LTE | LT | GT | GTE | EQ | NEQ;
