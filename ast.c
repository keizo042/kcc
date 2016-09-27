#include "ast.h"
#include <stdint.h>




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
    tag_t t;
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
