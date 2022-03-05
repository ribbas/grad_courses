/* Cminus.g4 */
/* Sabbir Ahmed */
/* 3/4/22 */
/* BNF grammar implementation for C-Minus BNF syntax outlined by Louden */

grammar Cminus;

@parser::preinclude {
    #include "../Symtab.hpp"
}
@parser::members {
    SymbolTable symtab;
	bool mainDeclared = false;

	bool declareFun(std::string funcName) {
		if (!symtab.contains(funcName)) {
			std::cout << "adding " << funcName << '\n';
			return true;
		} else {
			return false;
		}
	}

	void declareMain(std::string funcName) {
		if (funcName == "main") {
			std::cout << "declaring main\n";
			mainDeclared = true;
		}
	}

	bool canDeclareFun(std::string funcName) {
		declareMain(funcName);
		if (mainDeclared && !(funcName == "main")) {
			return false;
		} else {
			symtab.define(funcName, "func");
			return true;
		}
	}

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
	type_specifier ID ('[' NUM ']')? ';' {symtab.define($ID.text, $type_specifier.text);};
type_specifier:
	'int' {symtab.define("int");}
	| 'void' {symtab.define("void");};
fun_declaration:
	type_specifier ID {canDeclareFun($ID.text)}? '(' params ')' compound_statement {symtab.define($ID.text, $type_specifier.text);
        };
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
return_statement: 'return' expression? ';';
expression: var '=' expression | simple_expression;
var: ID ('[' expression ']')?;
simple_expression:
	additive_expression (relop additive_expression)?;
relop: '<=' | '<' | '>' | '>=' | '==' | '!=';
additive_expression: additive_expression addop term | term;
addop: '+' | '-';
term: term mulop factor | factor;
mulop: '*' | '/';
factor: '(' expression ')' | var | call | NUM;
call: ID '(' args ')';
args: arg_list |;
arg_list: arg_list ',' expression | expression;
