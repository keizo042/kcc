#ifndef __KCC_PARSER_H
#define __KCC_PARSER_H
#include "ast.h"
#include "lex.h"

#define AST_DIGIT
#define AST_STRING
#define AST_OP
#define AST_UNIOP
#define AST_BINOP
#define AST_EXPRS
#define AST_EXPR
#define AST_EXPR_DEF
#define AST_EXPR_DEF_VAR
#define AST_EXPR_DEF_STRUCT
#define AST_STMTS
#define AST_STMT
#define AST_STMT_FUNC
#define AST_STMT_IF
#define AST_STMT_WHILE
#define AST_STMT_SWITCH_CASE
#define AST_STMT_FOR
#define AST_UNDEFINED

typedef struct ast_s ast_t;
struct ast_s {
    type_tag_t typ;
    union {
        int digit;
        char *str;
        op_t op;
        uniop_t uniop;
        binop_t binop;
        expr_t expr;
        exprs_t exprs;
        expr_def_var_t expr_def_var;
        expr_def_struct_t expr_def_struct;
        expr_def_t expr_def;
        stmt_while_t stmt_while;
        stmt_for_t stmt_for;
        stmt_switch_case_t stmt_switch_case;
        stmt_if_t stmt_if;
        stmt_def_func_t stmt_def_func;
        stmt_t stmt;
        stmts_t stmts;
        ast_t *t;
    } data;
};


typedef struct parser_stack_s parser_stack_t;
struct parser_stack_s {
    ast_t *data;
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
