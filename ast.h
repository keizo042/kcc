#ifndef __KCC_AST_H
#define __KCC_AST_H
#include <stdint.h>

typedef int type_tag_t;
typedef struct uniop_s uniop_t;
typedef struct binop_s binop_t;
typedef struct op_s op_t;
typedef struct expr_def_var_s expr_def_var_t;
typedef struct expr_def_struct_s expr_def_struct_t;
typedef struct expr_def_s expr_def_t;
typedef struct expr_funcall_s expr_funcall_t;
typedef struct expr_s expr_t;
typedef struct exprs_s exprs_t;
typedef struct stmt_while_s stmt_while_t;
typedef struct stmt_for_s stmt_for_t;
typedef struct stmt_switch_case_s stmt_switch_case_t;
typedef struct stmt_if_s stmt_if_t;
typedef struct stmt_def_func_s stmt_def_func_t;
typedef struct stmt_s stmt_t;
typedef struct stmts_s stmts_t;

#define UNIOP_UNDEF 0
#define UNIOP_INCR 1
#define UNIOP_DECR 2
struct uniop_s {
    unsigned int op;
    char *value;
};

#define BINOP_UNDEF 0
#define BINOP_PLUG 1
#define BINOP_MINUS 2
#define BINOP_MULTI 3
#define BINOP_DIV 4
#define BINOP_PLUSEQ 5
#define BINOP_MINEQ 6
#define BINOP_MULTIEQ 7
#define BINOP_DIVEQ 8

struct binop_s {
    unsigned int op;
    char *lvalue;
    char *rvalue;
};

struct op_s {
    union {
        uniop_t *uniop;
        binop_t *binop;
    } data;
};

struct expr_def_var_s {
    char **keywords;
    char *type;
    char **varname;
    char **varvalue;
};

struct expr_def_struct_s {
    char *sym;
    expr_def_var_t **vars;
};

#define EXPR_DEF_VAR 1
#define EXPR_DEF_STRUCT 2

struct expr_def_s {
    type_tag_t typ;
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


#define EXPR_DEF 1
#define EXPR_FUNCALL 2
struct expr_s {
    type_tag_t t;
    union {
        char *sym;
        op_t op;
        expr_def_t def;
        expr_funcall_t funcall;
    } data;
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
    char *typ;
    char *sym;
    int argc;
    char **args;
    stmts_t *stmt;
};


#define STMT_EXPRS 1
#define STMT_IF 2
#define STMT_WHILE 3
#define STMT_FOR 4
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
