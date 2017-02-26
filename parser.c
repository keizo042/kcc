#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lex.h"
#include "parser.h"

typedef enum {
    PARSE_STATE_ACCEPT,
    PARSE_STATE_REJECT,
    PARSE_STATE_INIT,

    PARSE_STATE_1,
    PARSE_STATE_2,
    PARSE_STATE_3,
    PARSE_STATE_4,
    PARSE_STATE_5,
    PARSE_STATE_6,
    PARSE_STATE_7,
    PARSE_STATE_8,
} parser_state_machine_status_t;


struct elem_t;
typedef struct elem_t elem_t;

struct parser_state_machine_stack_t;
typedef struct parser_state_machine_stack_t parser_state_machine_stack_t;

struct parser_state_machine_t;
typedef struct parser_state_machine_t parser_state_machine_t;

//
//
//
// * internal main parser state *//
//
//
//


typedef struct parser_state_machine_t {
    parser_state_machine_stack_t *stack;
    int stack_size; // make error handling easily.

    parser_state_machine_status_t status;
    parser_state *parser;

    lex_token_list_t *peek;

} parser_state_machine_t;

//
//
//
/* export api function */
//
//
//

static parser_state_machine_t *parser_state_machine_init(parser_state *parser) {
    parser_state_machine_t *state = malloc(sizeof(parser_state_machine_t));
    state->status                 = PARSE_STATE_INIT;
    state->stack                  = NULL;
    state->stack_size             = 0;

    state->parser = parser;
    state->peek   = parser->start;
    return state;
}


parser_state *parser_state_init(lex_state *lexer) {
    parser_state *state = (parser_state *)malloc(sizeof(parser_state));
    state->start        = lexer->start;
    state->stream       = state->start;
    state->errmsg       = NULL;
    state->err          = 0;
    return state;
}

//
// all we need internal api is.  parser state machine runner
//
static parser_state_machine_status_t parser_state_machine(parser_state_machine_t *state);

// parser_state_run() handle internal state, and run it.
int parser_state_run(parser_state *parser) {
    parser_state_machine_status_t rc = PARSE_STATE_REJECT;
    parser_state_machine_t *state    = parser_state_machine_init(parser);

    rc = parser_state_machine(state);
    if (rc == PARSE_STATE_REJECT) {
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
// *** internal ***
//
//
//

//
//  * stack machine utility
//

typedef struct elem_t {
    ast_type_t node_typ;
    union {
        comment_t *comment;
        stmts_t *node;
        stmt_t *stmt;
        stmt_if_t *stmt_if;
        stmt_while_t *stmt_while;

        expr_t *expr;
        expr_assign_t *expr_asign;
        expr_funcall_t *expr_funcall;
        expr_binop_t *expr_binop;
        expr_uniop_t *expr_uniop;

        decl_t *decl;
        decl_var_t *decl_var;
        decl_struct_t *decl_struct;
        decl_func_t *decl_func;

        token_t *token;

    } body;

} elem_t;

typedef struct parser_state_machine_stack_t {
    parser_state_machine_stack_t *prev;
    elem_t *e;
} parser_state_machine_stack_t;

static int parser_state_machine_stack_push(parser_state_machine_t *state, elem_t *e) {
    parser_state_machine_stack_t *s = malloc(sizeof(parser_state_machine_stack_t));
    s->e                            = e;
    s->prev                         = state->stack;
    state->stack                    = s;
    return 0;
}

static elem_t *parser_state_machine_stack_pop(parser_state_machine_t *state) {
    elem_t *e;
    parser_state_machine_stack_t *s;
    s = state->stack;
    if (!s) {
        return NULL;
    }

    e            = s->e;
    state->stack = s->prev;
    free(s);

    return e;
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

//
//
//
// *** internal api ***
//
//
//

static parser_state_machine_status_t parser_state_machine(parser_state_machine_t *state) {
    switch (state->status) {
    case PARSE_STATE_REJECT:
        return PARSE_STATE_REJECT;
    case PARSE_STATE_ACCEPT:
        return PARSE_STATE_ACCEPT;
    case PARSE_STATE_1:
    case PARSE_STATE_2:
    case PARSE_STATE_3:
    case PARSE_STATE_4:
    case PARSE_STATE_5:
    case PARSE_STATE_6:
    default:
        return PARSE_STATE_REJECT;
    }
}
