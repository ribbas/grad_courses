/* Cminus.g4 */
/* by Allyn Shell */
/* February 2022 */

grammar Cminus;

@parser::visitorpreinclude {
#include "SemPred.h"
}
@parser::visitordeclarations {
SemanticPredicate semantics;
}

// Lexical Analyzer Rules

IF: 'if';
ELSE: 'else';
WHILE: 'while';
RETURN: 'return';
INT: 'int';
VOID: 'void';

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
var_declaration: INT ID ('[' NUM ']')? ';';
fun_declaration:
	fun_type_specifier ID '(' (param (',' param)* | VOID) ')' compound_stmt;
fun_type_specifier: INT | VOID;
param: INT ID ('[' ']')?;
compound_stmt: '{' var_declaration* statement* '}';
statement:
	compound_stmt
	| selection_stmt
	| iteration_stmt
	| assignment_stmt
	| return_stmt
	| exp ';'
	| ';';
selection_stmt:
	IF '(' (exp | relational_exp) ')' statement (ELSE statement)?;
iteration_stmt: WHILE '(' (exp | relational_exp) ')' statement;
assignment_stmt:
	ID ('[' exp ']')? '=' (exp | relational_exp) ';';
return_stmt: RETURN return_value? ';';
return_value: exp | relational_exp;
exp:
	exp multop exp						# mult_exp
	| exp addop exp						# add_exp
	| '(' (exp | relational_exp) ')'	# paren_exp
	| ID ('[' exp ']')?					# val_exp
	| ID '(' (exp (',' exp)*)? ')'		# call_exp
	| NUM								# num_exp;
relational_exp: exp relop exp;
addop: '+' | '-';
multop: '*' | '/';
relop: '<=' | '<' | '>' | '>=' | '==' | '!=';
