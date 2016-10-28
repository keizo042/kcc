#ifndef __KCC_PARSER_H
#define __KCC_PARSER_H
#include "ast.h"
#include "lex.h"

#define AST_DIGIT 1
#define AST_STRING 2
#define AST_OP 3
#define AST_UNIOP 4
#define AST_BINOP 5
#define AST_EXPRS 6 
#define AST_EXPR 7
#define AST_EXPR_DEF 8 
#define AST_EXPR_DEF_VAR 9
#define AST_EXPR_DEF_STRUCT 10
#define AST_STMTS 11
#define AST_STMT 12
#define AST_STMT_FUNC 13
#define AST_STMT_IF 14
#define AST_STMT_WHILE 15
#define AST_STMT_SWITCH_CASE 16
#define AST_STMT_FOR 17
#define AST_UNDEFINED 18


typedef struct ast_s ast_t;
struct ast_s {
    type_tag_t typ;
    union {
        int digit;
        char *str;
        op_t op;
        uniop_t uniop;
        binop_t binop;
        exprs_t exprs;
        expr_t expr;
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
    lex_tok_stream_t *stream;
    parser_stack_t *stack;
    stmt_t *result;
    int err;
};
typedef struct parser_state parser_state;

ast_t * parser_stack_pop(parser_state *);
int * parser_stack_push(parser_state *, ast_t *);
parser_state *parse(lex_state *);

int ast_pp(ast_t *);
#endif
