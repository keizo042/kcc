#ifndef __KCC_AST_H
#define __KCC_AST_H

typedef int tag_t;

struct expr_def_function_s;
typedef struct expr_def_func_s expr_def_func_t;

struct expr_def_var_s;
typedef struct expr_def_var_s expr_def_var_t;

struct expr_def_s;
typedef struct expr_def_s expr_def_t;

struct uniop_s;
typedef struct uniop_s uniop_t;

struct binop_s;
typedef struct binop_s binop_t;

struct op_s;
typedef struct op_s op_t;

struct expr_s;
typedef struct expr_s expr_t;

struct exprs_s;
typedef struct exprs_s exprs_t;

struct stmt_s;
typedef struct stmt_s stmt_t;

struct stmts_s;
typedef struct stmts_s stmts_t;
#endif
