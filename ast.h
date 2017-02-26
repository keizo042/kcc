#ifndef AST_H
#define AST_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    AST_UNDEFINED,

    AST_COMMENT,

    AST_STMTS,
    AST_STMT,
    AST_STMT_IF,
    AST_STMT_FOR,
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

    AST_TYPE,
    AST_STRING,
    AST_IDENT,
    AST_DIGIT,
} ast_type_t;

typedef enum {
    BINOP_PLUS,
    BINOP_MINUS,
    BINOP_MULTI,
    BINOP_DIV,

    BINOP_AND,
    BINOP_OR,
} binop_op_t;

typedef enum {
    UNIOP_INCR,
    UNIOP_DECR,
    UNIOP_NOT,
} uniop_op_t;

struct comment_t;
typedef struct comment_t comment_t;

struct stmts_t;
typedef struct stmts_t stmts_t;

struct stmt_t;
typedef struct stmt_t stmt_t;

struct stmt_if_t;
typedef struct stmt_if_t stmt_if_t;

struct stmt_for_t;
typedef struct stmt_for_t stmt_for_t;

struct stmt_while_t;
typedef struct stmt_while_t stmt_while_t;

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

struct ident_t;
typedef struct ident_t ident_t;

struct string_t;
typedef struct string_t string_t;

struct digit_t;
typedef struct digit_t digit_t;

struct type_t;
typedef struct type_t type_t;



//
//
//
// * decl
//
//
//

typedef struct comment_t { char *text; } comment_t;

typedef struct stmts_t {
    ast_type_t stmts_typ;
    union {
        stmt_t *stmt;
        expr_t *expr;
        decl_t *decl;
    } body;
    stmts_t *next;
} stmts_t;

typedef struct stmt_t {
    ast_type_t stmt_typ;
    union {
        expr_t *expr;
        stmt_if_t *stmt_if;
        stmt_for_t *stmt_for;
        stmt_while_t *stmt_while;
    } body;
} stmt_t;

typedef struct stmt_if_t {
    expr_t *p; 
    stmt_t *if_true_body;

    int hasElse;
    stmt_t *if_else_body;
} stmt_if_t;

typedef struct stmt_for_t {
    expr_t *init;
    expr_t *p;
    expr_t *succ;
    stmt_t *stmt;
}stmt_for_t;

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
        digit_t *digit;
        string_t *str;
        ident_t *ident;
    } body;
} expr_t;

typedef struct expr_funcall_t {
    ident_t *fnsym;
    expr_t **args;
} expr_funcall_t;

typedef struct expr_binop_t {
    binop_op_t op;
    expr_t *lval;
    expr_t *rval;
} expr_binop_t;

typedef struct expr_uniop_t {
    char op;
    expr_t *val;
} expr_uniop_t;

typedef struct expr_assign_t {
    ident_t *ident;
    expr_t *expr;
} expr_assign_t;


typedef struct decl_t {
    ast_type_t decl_typ;
    union {
        decl_func_t *decl_func;
        decl_var_t *decl_var;
        decl_struct_t *decl_struct;
    } body;
} decl_t;

typedef struct decl_func_t {
    type_t *typ;
    ident_t *sym;
    decl_var_t **args;
    stmt_t *stmt;
} decl_func_t;

typedef struct decl_var_t { ast_type_t decl_var_typ; } decl_var_t;

typedef struct decl_struct_t {
    ast_type_t decl_struct_typ;
    union {
        ident_t *ident;
        decl_var_t **member;
    } body;
} decl_struct_t;

typedef struct type_t {
    ast_type_t type_typ;
    union {
    } body;
} type_t;

typedef struct digit_t { int digit; } digit_t;

typedef struct string_t { char *str; } string_t;


#endif
