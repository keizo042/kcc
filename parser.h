#ifndef __KCC_PARSER_H
#define __KCC_PARSER_H
#include "ast.h"
#include "lex.h"

typedef struct ast_s ast_t;
struct ast_s {
    type_tag_t typ;
    union {
        expr_def_var_t expr_def_var;
        expr_def_struct_t expr_def_struct;
        expr_def_t expr_def;
        uniop_t uniop;
        binop_t binop;
        op_t op;
        expr_t expr;
        exprs_t exprs;
        stmt_while_t stmt_while;
        stmt_for_t stmt_for;
        stmt_switch_case_t stmt_switch_case;
        stmt_if_t stmt_if;
        stmt_def_func_t stmt_def_func;
        stmt_t stmt;
        stmts_t stmts;
    } data;
};


typedef struct parser_stack_s parser_stack_t;
struct parser_stack_s {

    parser_stack_t *prev;
};

struct parser_state {
    char *sym;
    lex_tok_stream_t *stream;
    parser_stack_t *stack;
    stmt_t *result;
    int err;
};
typedef struct parser_state parser_state;
parser_state *parse(lex_state *);
#endif
