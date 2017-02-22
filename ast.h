#ifndef AST_H
#define AST_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    AST_UNDEFINED,

    AST_COMMENT,

    AST_NODE,
    AST_STMT,
    AST_STMT_IF,
    AST_STMT_WHILE,
    AST_STMT_CASE,

    AST_EXPR,
    AST_EXPR_BINOP,
    AST_EXPR_UNIOP,
    AST_EXPR_FUNCALL,
    AST_DECL,
    AST_DECL_VAR,
    AST_DECL_STRUCT,
    AST_DECL_FUNC,
    AST_TOKEN,
    AST_TOKEN_UNDEFINED,
    AST_TOKEN_STRING,
    AST_TOKEN_IDENT,
    AST_TOKEN_DIGIT,
} ast_type_t;

struct comment_t;
typedef struct comment_t comment_t;

struct stmt_t;
typedef struct stmt_t stmt_t;

struct expr_t;
typedef struct expr_t expr_t;

struct expr_assign_t;
typedef struct expr_assign_t expr_assign_t;

struct expr_funcall_t;
typedef struct expr_funcall_t expr_funcall_t;

struct expr_uniop_t;
typedef struct expr_uniop_t expr_uniop_t;

struct expr_binop_t;
typedef struct expr_binop_t expr_binop_t;

struct decl_t;
typedef struct decl_t decl_t;

struct decl_var_t;
typedef struct decl_var_t decl_var_t;

struct decl_struct_t;
typedef struct decl_struct_t decl_struct_t;

struct decl_func_t;
typedef struct decl_func_t decl_func_t;

struct node_t;
typedef struct node_t node_t;

typedef struct comment_t { char *text; } comment_t;

typedef struct node_t {
    ast_type_t node_typ;
    union {
        stmt_t *stmt;
        expr_t *expr;
        decl_t *decl;
    } body;
    node_t *next;
} node_t;

typedef struct stmt_t {
    expr_t *expr;
    stmt_t *stmt;
} stmt_t;

typedef struct stmt_if_t {
    expr_t *exp1;
    expr_t *exp2;
    expr_t *exp3;
    stmt_t *if_true_body;

    int hasElse;
    stmt_t *if_else_body;
} stmt_if_t;

typedef struct stmt_while_t {
    expr_t *p;
    stmt_t *body;
} stmt_while_t;

typedef struct expr_t {
    ast_type_t expr_typ;
    union {
        expr_binop_t *binop;
        expr_uniop_t *uniop;
        expr_funcall_t *funcall;
        expr_assign_t *assign;
    } body;
} expr_t;

typedef struct expr_funcall_t {
} expr_funcall_t;

typedef struct expr_binop_t {
    char op;
    expr_t *lval;
    expr_t *rval;
} expr_binop_t;

typedef struct expr_uniop_t {
    char op;
    expr_t *val;
} expr_uniop_t;

typedef struct expr_assign_t {
} expr_assign_t;


typedef struct decl_t {
} decl_t;

typedef struct decl_func_t {
    ast_type_t decl_typ;
    union {
        decl_var_t *decl_var;
        decl_struct_t *decl_struct;
        decl_func_t *decl_func;
    } body;
} decl_func_t;

typedef struct decl_var_t {
} decl_var_t;

typedef struct decl_struct_t {
} decl_struct_t;

typedef struct token_t {
    ast_type_t token_typ;
    union {
        char *str;
        int digit;
        char *ident;
    } data;

    int pos;
    int line;
} token_t;

#endif
