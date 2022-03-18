grammar Cminus;

// Parser Rules

program: (var_declaration | fun_declaration)+ EOF;
var_declaration: 'int' ID ('[' NUM ']')? ';';
fun_declaration: ('int' | 'void') ID '(' (
		param (',' param)*
		| 'void'
	) ')' compound_stmt;
param: 'int' ID ('[' ']')?;
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
	'if' '(' (exp | relational_exp) ')' statement (
		'else' statement
	)?;
iteration_stmt:
	'while' '(' (exp | relational_exp) ')' statement;
assignment_stmt:
	ID ('[' exp ']')? '=' (exp | relational_exp) ';';
return_stmt: 'return' (exp | relational_exp)? ';';
exp:
	exp ('*' | '/') exp					# mult_exp
	| exp ('+' | '-') exp				# add_exp
	| '(' (exp | relational_exp) ')'	# paren_exp
	| ID ('[' exp ']')?					# val_exp
	| ID '(' (exp (',' exp)*)? ')'		# call_exp
	| NUM								# num_exp;
relational_exp: exp ('<=' | '<' | '>' | '>=' | '==' | '!=') exp;

//    Lexical Analyzer Rules

// 1 or more letters
ID: LETTER+;
fragment LETTER: [A-Za-z];

// 1 or more digits
NUM: DIGIT+;
fragment DIGIT: [0-9];

// comment and whitespace tokens get skipped
COMMENT: ('/*' (.)*? '*/' | '//' ~('\r' | '\n')*) -> skip;
WS: [ \t\r\n]+ -> skip;
