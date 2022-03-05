/* Cminus.g4 */
/* Sabbir Ahmed */
/* 3/4/22 */
/* BNF grammar implementation for C-Minus BNF syntax outlined by Louden */

grammar Cminus;

@parser::preinclude {
#include "../SemPred.hpp"
}
@parser::members {
SemanticPredicate semantics;
}

// 1 or more letters
ID: LETTER+;
fragment LETTER: [A-Za-z];

// 1 or more digits
NUM: DIGIT+;
fragment DIGIT: [0-9];

// comment and whitespace tokens get skipped
COMMENT: '/*' (.)*? '*/' -> skip;
WS: [ \t\r\n]+ -> skip;

program: declaration_list EOF;
declaration_list: declaration_list declaration | declaration;
declaration: var_declaration | fun_declaration;
var_declaration:
	type_specifier {$type_specifier.text == "int"}? ID (
		'[' NUM ']'
	)? ';' {semantics.addSymbol($ID.text, $type_specifier.text);};
type_specifier:
	'int' {semantics.addSymbol("int");}
	| 'void' {semantics.addSymbol("void");};
fun_declaration:
	type_specifier ID {semantics.canDeclareFunc($ID.text, $type_specifier.text)}? '(' params ')'
		compound_statement;
params: param_list | 'void';
param_list: param_list ',' param | param;
param: type_specifier ID ('[' ']')?;
compound_statement: '{' local_declarations statement_list '}';
local_declarations: local_declarations var_declaration |;
statement_list: statement_list statement |;
statement:
	expression_statement
	| compound_statement
	| selection_statement
	| iteration_statement
	| return_statement;
expression_statement: expression? ';';
selection_statement:
	'if' '(' expression ')' statement ('else' statement)?;
iteration_statement: 'while' '(' expression ')' statement;
return_statement:
	'return' ';'
	| 'return' expression ';' {semantics.checkReturnType($expression.text)}?;
expression: var '=' expression | simple_expression;
var: ID ('[' expression ']')? {semantics.checkSymbol($ID.text)}?;
simple_expression:
	additive_expression (relop additive_expression)?;
relop: '<=' | '<' | '>' | '>=' | '==' | '!=';
additive_expression: additive_expression addop term | term;
addop: '+' | '-';
term: term mulop factor | factor;
mulop: '*' | '/';
factor: '(' expression ')' | var | call | NUM;
call: ID '(' args ')' {semantics.checkSymbol($ID.text)}?;
args: arg_list |;
arg_list: arg_list ',' expression | expression;
