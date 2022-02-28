#include "FF_List.h"

FF_List expFirsts({NUM, ID, LPAREN});
FF_List expFollows({RPAREN, T_ERROR});

FF_List addOpFirsts({ADD, SUB});
FF_List addOpFollows({NUM, ID, LPAREN});

FF_List termFirsts({NUM, ID, LPAREN});
FF_List termFollows({ADD, SUB, RPAREN, T_ERROR});

FF_List mulOpFirsts({MULT, DIV});
FF_List mulOpFollows({NUM, ID, LPAREN});

FF_List factorFirsts({NUM, ID, LPAREN});
FF_List factorFollows({MULT, DIV, ADD, SUB, RPAREN, T_ERROR});

FF_List parenExpFirsts({LPAREN});
FF_List parenExpFollows({MULT, DIV, ADD, SUB, RPAREN, T_ERROR});
