#ifndef AST_H
#define AST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
typedef int32_t typ_t;

#define NODE_UNDEFINED 0
#define NODE_STMT 0x01
#define NODE_STMT_IF 0x02
#define NODE_STMT_WHILE 0x03
#define NODE_STMT_CASE 0x04
#define NODE_EXPR  0x05
#define NODE_EXPR_BINOP 0x06
#define NODE_EXPR_UNIOP 0x07
#define NODE_EXPR_FUNCALL 0x08
#define NODE_DECL 0x09
#define NODE_DECL_VAR 0x0a
#define NODE_DECL_STRUCT 0x0b
#define NODE_DECL_FUNC 0x0c
#define NODE_TOKEN  0x0d

#define TOKEN_UNDEFINED 0
#define TOKEN_STRING 0x01
#define TOKEN_IDENT 0x02
#define TOKEN_DIGIT 0x03
#define TOKEN_DIGIT_INT 0x04
#define TOKEN_DIGIT_FLOAT 0x05

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

struct decl_val_t;
typedef struct decl_val_t decl_val_t;

struct decl_struct_t;
typedef struct decl_struct_t decl_struct_t;

struct decl_func_t;
typedef struct decl_func_t decl_func_t;

struct node_t;
typedef struct node_t node_t;

typedef struct comment_t {
    char *text;
}comment_t;

typedef struct node_t {
    typ_t node_typ;
    union {
        stmt_t *stmt;
        expr_t *expr;
        decl_t *decl;
    }body;
    node_t *next;
}node_t;

typedef struct stmt_t {
    expr_t *expr;
    stmt_t *stmt;
}stmt_t;

typedef struct stmt_if_t {
    expr_t *exp1;
    expr_t *exp2;
    expr_t *exp3;
    stmt_t *if_true_body;

    int hasElse;
    stmt_t *if_else_body;
}stmt_if_t;

typedef struct stmt_while_t {
    expr_t *p;
    stmt_t *body;
}stmt_while_t;

typedef struct expr_t {
    typ_t expr_typ;
    union {
        expr_binop_t *binop;
        expr_uniop_t *uniop;
        expr_funcall_t *funcall;
        expr_assign_t *assign;
    }body;
}expr_t;

typedef struct expr_funcall_t {
}expr_funcall_t;

typedef struct expr_binop_t {
    char op;
    expr_t *lval;
    expr_t *rval;
}expr_binop_t;

typedef struct expr_uniop_t {
    char op;
    expr_t *val;
}expr_uniop_t;

typedef struct expr_assign_t {
}expr_assign_t;


typedef struct decl_t {
}decl_t;

typedef struct decl_func_t {
    typ_t decl_typ;
    union {
        decl_val_t *decl_val;
        decl_struct_t *decl_struct;
        decl_func_t *decl_func;
    }body;
}decl_func_t;

typedef struct decl_val_t {
}decl_val_t;

typedef struct decl_struct_t {
}decl_struct_t;

typedef struct token_t {
    typ_t token_typ;
    union {
        char *str;
        int digit;
        char *ident;
    };

    int pos;
    int line;
}token_t;

#endif
