#include "ast.h"


typedef int tag_t;

struct expr_s {
    char *sym;
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
