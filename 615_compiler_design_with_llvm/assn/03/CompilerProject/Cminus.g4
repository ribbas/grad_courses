grammar Cminus;

program: declaration_list;
declaration_list: declaration_list declaration | declaration;
declaration: var_declaration | fun_declaration;
var_declaration:
	type_specifier ID ';'
	| type_specifier ID '[' NUMBER ']' ';';
type_specifier: 'int' | 'void';
fun_declaration:
	type_specifier ID '(' params ')' compound_statement;
params: param_list | 'void';
param_list: param_list ',' param | param;
param: type_specifier ID | type_specifier ID '[' ']';
compound_statement: '{' local_declarations statement_list '}';
local_declarations: var_declaration*;
statement_list: statement*;
statement:
	expression_statement
	| compound_statement
	| selection_statement
	| iteration_statement
	| return_statemet;
expression_statement: expression? ';';
selection_statement:
	'if' '(' expression ')' statement
	| 'if' '(' expression ')' statement 'else' statement;
iteration_statement: 'while' '(' expression ')' statement;
return_statemet: 'return' expression? ';';
expression: var '=' expression | simple_expression;
var: ID | ID '[' expression ']';
simple_expression:
	additive_expression relop additive_expression
	| additive_expression;
relop: '<=' | '<' | '>' | '>=' | '==' | '!=';
additive_expression: additive_expression addop term | term;
addop: '+' | '-';
term: term mulop factor | factor;
mulop: '*' | '/';
factor: '(' expression ')' | var | call | NUMBER;
call: ID '(' args ')';
args: arg_list?;
arg_list: arg_list ',' expression | expression;

COMMENT: '/*' (.)*? '*/' -> channel(HIDDEN);
ID: [a-zA-Z]+;
NUMBER: '0' | [1-9][0-9]*;
WS: [ \t\r\n]+ -> channel(HIDDEN);
