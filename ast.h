#ifndef __KCC_AST_H
#define __KCC_AST_H
#include <stdint.h>

typedef int type_tag_t;
typedef struct expr_def_var_s expr_def_var_t;
typedef struct expr_def_struct_s expr_def_struct_t;
typedef struct expr_def_s expr_def_t;
typedef struct uniop_s uniop_t;
typedef struct binop_s binop_t;
typedef struct op_s op_t;
typedef struct expr_s expr_t;
typedef struct exprs_s exprs_t;
typedef struct stmt_while_s stmt_while_t;
typedef struct stmt_for_s stmt_for_t;
typedef struct stmt_switch_case_s stmt_switch_case_t;
typedef struct stmt_if_s stmt_if_t;
typedef struct stmt_def_func_s stmt_def_func_t;
typedef struct stmt_s stmt_t;
typedef struct stmts_s stmts_t;

struct expr_def_var_s {
    char **keywords;
    char *type;
    char **varname;
    char **varvalue;
};

struct expr_def_struct_s {
    expr_def_var_t **vars;
};

struct expr_def_s {
    union {
        expr_def_var_t *var;
        expr_def_struct_t *srct;
    } data;
};

struct expr_funcall_s {
    char *sym;
    int argc;
    char **args;
};


struct uniop_s {
    char *op;
    char *value;
};

struct binop_s {
    char *op;
    char *lvalue;
    char *rvalue;
};

struct op_s {
    union {
        uniop_t *uniop;
        binop_t *binop;
    } data;
};

struct expr_s {
    union {
        char *sym;
        op_t *op;
    } data;
    type_tag_t t;
};

struct exprs_s {
    expr_t *expr;
    struct expr_s *next;
};


struct stmt_if_s {
    expr_t *expr;
};

struct stmt_for_s {
    expr_t *arg1;
    expr_t *arg2;
    expr_t *arg3;
    stmt_t *stmt;
};

struct stmt_switch_case_s {
    expr_t *expr;
    stmts_t *stmts;
};

struct stmt_while_s {
    expr_t *expr;
    stmt_t *stmt;
};

struct stmt_def_func_s {
    char *type;
    char *sym;
    int argc;
    char **args;
    stmts_t *stmt;
};

struct stmt_s {
    uint64_t id;
    union {
        exprs_t *exprs;
        stmt_if_t *ifstmt;
        stmt_while_t *whilestmt;
        stmt_for_t *forstmt;
    } data;
};

struct stmts_s {
    stmt_t *stmt;
    struct stmt_s *next;
};

#endif
