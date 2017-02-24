#include "ast.h"
#include "gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token_t token1 = {AST_TOKEN_DIGIT, .body.digit = 1, 0, 0};

token_t token2 = {AST_TOKEN_DIGIT, .body.digit = 2, 0, 0};


expr_t testdata_expr_token_1 = {
    AST_TOKEN, .body.token = &token1,
};

expr_t testdata_expr_token_2 = {
    AST_TOKEN, .body.token = &token2,
};

expr_binop_t testdata_expr_binop = {
    BINOP_PLUS, &testdata_expr_token_1, &testdata_expr_token_2,
};

expr_t testdata_expr = {
    AST_EXPR_BINOP, &testdata_expr_binop,
};

stmt_t testdata_stmt = {
    AST_EXPR, &testdata_expr,
};

stmts_t testdata_stmts = {
    AST_STMT, &testdata_stmt, NULL,

};

gen_info_t expect = {};

int main() {
    printf("not yet implemented\n");
    return 1;
}
