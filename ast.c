#include "ast.h"


typedef int tag_t;

struct uniop_s {
    char *op;
    char *value;
};

typedef struct uniop_s uniop_t;

struct binop_s {
    char  *op;
    char *lvalue;
    char *rvalue;
};

typedef struct binop_s binop_t;


struct op_s {
    union {
        uniop_t* uniop;
        binop_t* binop;
    }data;
};

typedef struct op_s op_t;


struct expr_s {
    union {
    char *sym;
    op_t *op;
    }data;
    tag_t t;
};

typedef struct expr_s expr_t;

struct exprs_s {
    expr_t *expr;
    struct expr_s *next;
};

typedef struct exprs_s exprs_t;

struct stmt_s {
    exprs_t *exprs;
};

struct stmt_s;
typedef struct stmt_s stmt_t;

struct stmts_s {
    stmt_t *stmt;
    struct stmt_s *next;

};

typedef struct stmts_s stmts_t;
