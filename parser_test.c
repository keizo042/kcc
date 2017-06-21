#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "parser.h"

int compare_stmt(stmt_t *lv, stmt_t *rv) { return 1; }

typedef int (*testfn_t)();

int test1() {
    //
    // ** before **
    //
    lex_token_t t1 = {
        "2", LEX_TOKEN_DIGIT,
    };

    lex_token_t t2 = {
        "+", LEX_TOKEN_PLUS,
    };

    lex_token_t t3 = {
        "1", LEX_TOKEN_DIGIT,
    };

    lex_token_t t4 = {
        "", LEX_TOKEN_EOF,
    };

    lex_token_list_t l1 = {};
    lex_token_list_t l2 = {};
    lex_token_list_t l3 = {};
    lex_token_list_t l4 = {};


    //
    // ** expect **
    //

    digit_t token1 = {1}, token2 = {1};

    expr_t expr_token1 = {AST_DIGIT, .body.digit = &token1},
           expr_token2 = {AST_DIGIT, .body.digit = &token2};

    expr_binop_t expr_binop = {BINOP_PLUS, &expr_token1, &expr_token2};

    expr_t expr = {AST_EXPR_BINOP, &expr_binop};
    stmt_t stmt = {AST_EXPR, &expr};

    stmt_t *result = NULL;
    stmts_t *r     = NULL;
    l1.token       = &t1;
    l2.token       = &t2;
    l3.token       = &t3;
    l4.token       = &t4;

    l1.next              = &l2;
    l2.next              = &l3;
    l3.next              = &l4;
    lex_state lexer      = {};
    lexer.start          = &l1;
    parser_state *parser = parser_state_init(&lexer);
    compare_stmt(result, &stmt);
    return 1;
}


testfn_t testcase[] = {test1, NULL};

int main(int argc, char *argv[]) {

    for (int i = 0; testcase[i] != NULL; i++) {
        testfn_t f = testcase[i];
        if (f()) {
            return 1;
        }
    }
    return 0;
}
