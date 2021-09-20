#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
calc.py

This file uses the lex and yacc scripts implemented in the PLY library (Python 
Lex-Yacc). All the functions defined in the file are rules for tokenizing and
parsing. The docstrings of the functions are also parsed as the grammar rules.
"""

from ply import lex, yacc

# tokens supported by the script
tokens = (
    "NUMBER",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIVIDE",
    "LPAREN",
    "RPAREN",
)

# rule for parsing a NUMBER token
def t_NUMBER(t):
    r"\d+"
    t.value = int(t.value)
    return t


# rules for parsing the operator tokens and the parenthesis
t_PLUS = r"\+"
t_MINUS = r"-"
t_TIMES = r"\*"
t_DIVIDE = r"/"
t_LPAREN = r"\("
t_RPAREN = r"\)"

# ignored characters
t_ignore = " "

# precedence rules for the arithmetic operators
precedence = (
    ("left", "PLUS", "MINUS"),
    ("left", "TIMES", "DIVIDE"),
    ("right", "UMINUS"),
)

# exit on token errors
def t_error(t):
    exit(t)


# grammar for EXPR
def p_statement_expr(p):
    "statement : expression"
    print(p[1])


# grammar for binary arithmetic operators
def p_expression_binop(p):
    """expression : expression PLUS expression
    | expression MINUS expression
    | expression TIMES expression
    | expression DIVIDE expression"""
    if p[2] == "+":
        p[0] = p[1] + p[3]
    elif p[2] == "-":
        p[0] = p[1] - p[3]
    elif p[2] == "*":
        p[0] = p[1] * p[3]
    elif p[2] == "/":
        p[0] = p[1] / p[3]


# grammar for UNARY MINUS
def p_expression_uminus(p):
    "expression : MINUS expression %prec UMINUS"
    p[0] = -p[2]


# grammar for EXPR between LPAREN and RPAREN
def p_expression_group(p):
    "expression : LPAREN expression RPAREN"
    p[0] = p[2]


# grammar for NUMBER
def p_expression_number(p):
    "expression : NUMBER"
    p[0] = p[1]


# exit on grammar errors
def p_error(p):
    exit(p)


# build the lexer
lex.lex()
yacc.yacc()

# parse an example input string
yacc.parse("-1 + (2 * 3 + 4) * -5")
