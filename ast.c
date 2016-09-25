#include "ast.h"


struct expr_def_func_s {
    char *type;
    char *sym;
    int argc;
    char **args;
    stmts_t *stmt;
};


struct expr_def_var_s {
    char **keywords;
    char *type;
    char **varname;
    char **varvalue;
};

struct expr_def_s {
    union {
        expr_def_var_t *var;
        expr_def_func_t *f;
    }data;
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
    char  *op;
    char *lvalue;
    char *rvalue;
};

struct op_s {
    union {
        uniop_t* uniop;
        binop_t* binop;
    }data;
};

struct expr_s {
    union {
    char *sym;
    op_t *op;
    }data;
    tag_t t;
};

struct exprs_s {
    expr_t *expr;
    struct expr_s *next;
};

struct stmt_s {
    exprs_t *exprs;
};

struct stmts_s {
    stmt_t *stmt;
    struct stmt_s *next;

};
