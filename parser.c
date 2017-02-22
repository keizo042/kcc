#include "parser.h"
#include "ast.h"
#include "lex.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PARSE_OK,
    PARSE_ERROR,
    PARSE_CONTINUE,

    PARSE_NODE,

    PARSE_DECL,
    PARSE_DECL_STRUCT,
    PARSE_DECL_VAR,
    PARSE_DECL_FUNC,

    PARSE_STMT,
    PARSE_STMT_STRUCT,
    PARSE_STMT_IF,
    PARSE_STMT_WHILE,

    PARSE_EXPR,
    PARSE_EXPR_FUNCALL,
    PARSE_EXPR_BINOP_PLUS_OR_MINUS,
    PARSE_EXPR_BINOP_MULTI_OR_DIV
} parser_state_status_t;

typedef struct elem_t {
    ast_type_t node_typ;
    union {
        comment_t *comment;
        stmt_t *stmt;
        stmt_if_t *stmt_if;
        stmt_while_t *stmt_while;

        expr_t *expr;
        expr_assign_t *expr_asign;
        expr_funcall_t *expr_funcall;
        expr_binop_t *expr_binop;
        expr_uniop_t *expr_uniop;

        decl_t *decl;
        decl_var_t * decl_var;
        decl_struct_t *decl_struct;
        decl_func_t *decl_func;

    } body;

} elem_t;

typedef struct parser_stack_t { parser_stack_t *prev; } parser_stack_t;

static parser_state_status_t parser_state_machine(parser_state *state);

parser_state *parser_state_init(lex_state *lexer) {
    parser_state *state = (parser_state *)malloc(sizeof(parser_state));
    state->start        = lexer->start;
    state->stream       = state->start;
    state->stack_size   = 0;
    state->stack        = NULL;
    state->err          = 0;
    return state;
}

int parser_state_run(parser_state *state) {

    parser_state_status_t rc = PARSE_CONTINUE;

    while (rc == PARSE_CONTINUE) {
        rc = parser_state_machine(state);
    }
    if (rc == PARSE_ERROR) {
        return 1;
    }
    return 0;
}
const char *parser_state_error(parser_state *state) {
    if (state->err) {
        return state->errmsg;
    } else {
        return "success";
    }
}

//
//
//
// *** internal api ***
//
//
//

static parser_state_status_t state_machine_stmt(parser_state *);
static parser_state_status_t state_machine_stmt_if(parser_state *);
static parser_state_status_t state_machine_stmt_while(parser_state *);

static parser_state_status_t state_machine_expr_binop(parser_state *);  // + or -
static parser_state_status_t state_machine_expr_binop2(parser_state *); // * or /
static parser_state_status_t state_machine_expr_uniop(parser_state *);  //
static parser_state_status_t state_machine_expr_funcall(parser_state *status);

static parser_state_status_t state_machine_decl_struct(parser_state *);
static parser_state_status_t state_machine_decl_var(parser_state *);
static parser_state_status_t state_machine_decl_func(parser_state *);

static parser_state_status_t parser_state_machine(parser_state *state) {
    switch (state->stream->token->typ) {
    case LEX_TOKEN_DIGIT:
    case LEX_TOKEN_STRING:
    case LEX_TOKEN_IDENT:
        return PARSE_ERROR;
    default:
        state->err    = 1;
        state->errmsg = "top: not yet impmenented";
        return PARSE_ERROR;
    }
}



///
///
///
/// *** functions for debug purpose ***
///
///
///

int parser_state_print(parser_state *state) {
    int nest_size = 0;
    return 1;
}
