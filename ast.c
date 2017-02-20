#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef int typ_t;

#define NODE_UNDEFINED 0
#define NODE_STMT 
#define NODE_STMT_IF
#define NODE_STMT_WHILE 
#define NODE_STMT_CASE
#define NODE_EXPR 
#define NODE_EXPR_BINOP
#define NODE_EXPR_UNIOP
#define NODE_EXPR_FUNCALL
#define NODE_DECL
#define NODE_DECL_VAR
#define NODE_DECL_FUNC
#define NODE_DECL_STRUCT
#define NODE_TOKEN 

#define TOKEN_STRING
#define TOKEN_IDENT
#define TOKEN_DIGIT
#define TOKEN_DIGIT_INT
#define TOKEN_DIGIT_FLOAT

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

struct node_t;
typedef struct node_t node_t;

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
}token_t;

