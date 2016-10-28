#include "parser.h"
#include "ast.h"
#include "lex.h"
#include <stdlib.h>
#include <string.h>


int parse_start(parser_state *);
int parse_uniop(parser_state *state);
int parse_binop(parser_state *state);
int parse_expr_def_struct(parser_state *state);
int parse_expr_def_var(parser_state *state);
int parse_exprs(parser_state *state);
int parse_expr(parser_state *state);
int parse_stmts(parser_state *state);
int parse_stmt(parser_state *state);
int parse_if_stmt(parser_state *state);
int parse_switch_stmt(parser_state *state);

ast_t *parser_stack_pop(parser_state *state) {
    parser_stack_t *t = NULL;
    if (state->stack == NULL) {
        return NULL;
    }
    t            = state->stack;
    state->stack = t->prev;
    if (t->data == NULL) {
        return NULL;
    }
    return t->data;
}

int *parser_stack_push(parser_state *state, ast_t *data) {
    parser_stack_t *t = malloc(sizeof(parser_stack_t));
    t->prev           = state->stack;
    t->data           = data;
    state->stack      = t;
    return 0;
}

parser_state *parse(lex_state *lexer) {
    parser_state *parser = NULL;
    parser               = malloc(sizeof(parser_state));
    parser->stream       = lexer->head;
    parse_start(parser);
    return parser;
}

int parse_start(parser_state *state) {

    return parse_stmts(state);
    switch (state->stream->token->typ) {
    case LEX_TOKEN_END:
    case LEX_TOKEN_DIGIT:
    case LEX_TOKEN_STRING:
    case LEX_TOKEN_PLUS:
    case LEX_TOKEN_MINUS:
    case LEX_TOKEN_DIV:
    case LEX_TOKEN_MULTI:
    case LEX_TOKEN_EQ:
    case LEX_TOKEN_LESS:
    case LEX_TOKEN_MORE:
    case LEX_TOKEN_BRACE_L:
    case LEX_TOKEN_BRACE_R:
    case LEX_TOKEN_BRACKET_L:
    case LEX_TOKEN_BRACKET_R:
    case LEX_TOKEN_SQUARE_BRACKET_L:
    case LEX_TOKEN_SQUARE_BRACKET_R:
    case LEX_TOKEN_CONNMA:
    case LEX_TOKEN_CORON:
    case LEX_TOKEN_SWITCH:
    case LEX_TOKEN_CASE:
    case LEX_TOKEN_GOTO:
    case LEX_TOKEN_IF:
    case LEX_TOKEN_WHILE:
        return parse_stmt(state);
    case LEX_TOKEN_ELSE:
    case LEX_TOKEN_IDENT:
    case LEX_TOKEN_TYPE:
    case LEX_TOKEN_RETURN:
    case LEX_TOKEN_KEYWORD:
    case LEX_TOKEN_EXCLAMATION:
    case LEX_TOKEN_QUESTION:
    case LEX_TOKEN_EOF:
    default:
        exit(-1);
    }
    return 0;
}

int parse_stmts(parser_state *state) {
    parse_stmt(state);
    return 0;
}

int parse_stmt(parser_state *state) {

    switch (state->stream->token->typ) {
    case LEX_TOKEN_IF:
        return parse_if_stmt(state);
    case LEX_TOKEN_SWITCH:
        return parse_switch_stmt(state);
    default:
        parse_exprs(state);
    }
    return 0;
}

int parse_if_stmt(parser_state *state) {
    ast_t *ini = NULL, *p = NULL, *succ = NULL;
    parse_expr(state);
    parse_expr(state);
    parse_expr(state);
    succ = parser_stack_pop(state);
    if (succ) {
        return -1;
    }
    p = parser_stack_pop(state);
    if (p) {
        return -1;
    }
    ini = parser_stack_pop(state);
    if (ini) {
        return -1;
    }
    parse_stmts(state);
    return 0;
}

int parse_switch_stmt(parser_state *state) {
    parse_stmts(state);
    return 0;
}
int parse_exprs(parser_state *state) { return -1; }
int parse_expr(parser_state *state) {
    switch (state->stream->token->typ) {
    default:
        return -1;
    }
    return 0;
}

int parse_expr_def_var(parser_state *state) {
    switch (state->stream->token->typ) {
    default:
        return -1;
    }
    return 0;
}
int parse_expr_def_struct(parser_state *state) {
    switch (state->stream->token->typ) {
    default:
        return -1;
    }
    return 0;
}

int parse_binop(parser_state *state) {
    ast_t *lval = NULL, *rval = NULL;
    parser_stack_pop(state);
    if (lval == NULL) {
        return -1;
    }
    parse_expr(state);
    if (rval == NULL) {
        return -1;
    }
    return 0;
}
int parse_uniop(parser_state *state) {
    ast_t *data = NULL;
    switch (state->stream->token->typ) {
    default:
        return -1;
    }
    data = parser_stack_pop(state);
    if (data == NULL) {
        return -1;
    }
    return 0;
}


int ast_pp(ast_t *ast)
{
    if(ast == NULL)
    {
        return -1;
    }
    switch(ast->typ)
    {
        default:
            return -1;
    }
}

