/* Cminus.g4 */
/* Sabbir Ahmed */
/* 3/12/22 */
/* BNF grammar implementation for C-Minus BNF syntax outlined by Louden */

grammar Cminus;

IF: 'if';
ELSE: 'else';
WHILE: 'while';
RETURN: 'return';
INT: 'int';
VOID: 'void';

COMMA: ',';
SEMICOLON: ';';
LBRACKET: '[';
RBRACKET: ']';
LPAREN: '(';
RPAREN: ')';

// 1 or more letters
ID: LETTER+;
fragment LETTER: [A-Za-z];

// 1 or more digits
NUM: DIGIT+;
fragment DIGIT: [0-9];

// comment and whitespace tokens get skipped
COMMENT: ('/*' (.)*? '*/' | '//' ~('\r' | '\n')*) -> skip;
WS: [ \t\r\n]+ -> skip;

program: declaration_list EOF;
declaration_list: declaration_list declaration | declaration;
declaration: var_declaration | fun_declaration;
var_declaration:
	type_specifier ID (LBRACKET NUM RBRACKET)? SEMICOLON {
		semantics.isValidVarType($type_specifier.text)}? {
			semantics.addSymbol($ID.text, $type_specifier.text);};
type_specifier: INT | VOID;
fun_declaration:
	type_specifier ID {semantics.canDeclareFunc($ID.text, $type_specifier.text)}? LPAREN params
		RPAREN compound_statement;
params:
	param_list {semantics.setNumArgs($param_list.text);}
	| VOID;
param_list: param_list COMMA param | param;
param:
	type_specifier {semantics.isValidVarType($type_specifier.text)}? ID (
		LBRACKET RBRACKET
	)? {semantics.addSymbol($ID.text, $type_specifier.text);};
compound_statement: '{' local_declarations statement_list '}';
local_declarations: local_declarations var_declaration |;
statement_list: statement_list statement |;
statement:
	expression_statement
	| compound_statement
	| selection_statement
	| iteration_statement
	| return_statement;
expression_statement: expression? SEMICOLON;
selection_statement:
	IF LPAREN simple_expression RPAREN statement (ELSE statement)?;
iteration_statement:
	WHILE LPAREN simple_expression RPAREN statement;
return_statement:
	RETURN SEMICOLON {semantics.checkReturnType()}?
	| RETURN simple_expression SEMICOLON {semantics.checkReturnType($simple_expression.text)}?;
expression:
	var '=' simple_expression {semantics.canReturn($simple_expression.text)}?
	| simple_expression;
var:
	ID (LBRACKET expression RBRACKET)? {semantics.checkSymbol($ID.text)}?;
simple_expression:
	additive_expression (relop additive_expression)?;
relop: '<=' | '<' | '>' | '>=' | '==' | '!=';
additive_expression: additive_expression addop term | term;
addop: '+' | '-';
term: term mulop factor | factor;
mulop: '*' | '/';
factor: LPAREN expression RPAREN | var | call | NUM;
call:
	ID {semantics.checkSymbol($ID.text)}? {semantics.setCurFuncName($ID.text);} LPAREN args RPAREN;
args: arg_list {semantics.isValidNumArgs($arg_list.text)}? |;
arg_list: arg_list COMMA expression | expression;
