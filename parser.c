#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lex.h"
#include "parser.h"

typedef enum {
    PARSE_BEFORE,
    PARSE_ERROR,
    PARSE_OK,
    PARSE_END,

    PARSE_STMTS,
    PARSE_STMT,
    PARSE_STMT_IF,
    PARSE_STMT_WHILE,

    PARSE_DECL,
    PARSE_DECL_VAR,
    PARSE_DECL_STRUCT,

    PARSE_EXPR,
    PARSE_EXPR_BINOP,
    PARSE_EXPR_BINOP_PLUS_OR_MINUS,
    PARSE_EXPR_BINOP_MULTI_OR_DIV,

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
    int stack_size;

    parser_state_machine_status_t status;
    parser_state *parser;

    lex_token_list_t *prev;
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
    state->status                 = PARSE_BEFORE;
    state->stack                  = NULL;
    state->stack_size             = 0;

    state->parser = parser;
    state->prev   = NULL;
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
    parser_state_machine_status_t rc = PARSE_ERROR;
    parser_state_machine_t *state    = parser_state_machine_init(parser);

    rc = parser_state_machine(state);
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



//
//
//
// *** internal api ***
//
//
//

// stmt
static parser_state_machine_status_t parser_state_machine_stmts(parser_state_machine_t *);

static parser_state_machine_status_t parser_state_machine_stmt(parser_state_machine_t *);
static parser_state_machine_status_t parser_state_machine_stmt_if(parser_state_machine_t *);
static parser_state_machine_status_t parser_state_machine_stmt_while(parser_state_machine_t *);

// expr
static parser_state_machine_status_t parser_state_machine_expr(parser_state_machine_t *);
static parser_state_machine_status_t
parser_state_machine_expr_binop_e(parser_state_machine_t *); // + or -
static parser_state_machine_status_t
parser_state_machine_expr_binop_t(parser_state_machine_t *); // * or /
static parser_state_machine_status_t parser_state_machine_expr_uniop(parser_state_machine_t *); //
static parser_state_machine_status_t
parser_state_machine_expr_funcall(parser_state_machine_t *status);

// decl
static parser_state_machine_status_t parser_state_machine_decl(parser_state_machine_t *);
static parser_state_machine_status_t parser_state_machine_decl_struct(parser_state_machine_t *);
static parser_state_machine_status_t parser_state_machine_decl_var(parser_state_machine_t *);
static parser_state_machine_status_t parser_state_machine_decl_func(parser_state_machine_t *);

// loop point
static parser_state_machine_status_t parser_state_machine(parser_state_machine_t *state) {
    switch (state->status) {
    case PARSE_BEFORE:
        return parser_state_machine_stmts(state);
    case PARSE_STMT:
    case PARSE_EXPR:
        return parser_state_machine_expr(state);
    case PARSE_EXPR_BINOP:
        return parser_state_machine_expr_binop_e(state);
    case PARSE_EXPR_BINOP_PLUS_OR_MINUS:
        return parser_state_machine_expr_binop_e(state);
    case PARSE_EXPR_BINOP_MULTI_OR_DIV:
        return parser_state_machine_expr_binop_t(state);
    case PARSE_OK:
        return PARSE_END;
    /* shoud not reach there. */
    default:
        return PARSE_ERROR;
    }
}

static parser_state_machine_status_t parser_state_machine_stmts(parser_state_machine_t *state) {
    lex_token_t *token = NULL;
    lex_token_list_get(state->peek, token);
    if (!token) {
        return PARSE_ERROR;
    }
    switch (token->typ) {
    case LEX_TOKEN_DIGIT:
    case LEX_TOKEN_TYPE:
        return parser_state_machine_decl(state);
    case LEX_TOKEN_KEYWORD:
    default:
        break;
    }
    return PARSE_STMTS;
}
static parser_state_machine_status_t parser_state_machine_stmt(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t parser_state_machine_stmt_if(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t
parser_state_machine_stmt_while(parser_state_machine_t *state) {
    return PARSE_ERROR;
}

static parser_state_machine_status_t parser_state_machine_expr(parser_state_machine_t *state) {
    return PARSE_ERROR;
}

static parser_state_machine_status_t
parser_state_machine_expr_binop_e(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t
parser_state_machine_expr_binop_t(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t
parser_state_machine_expr_uniop(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t
parser_state_machine_expr_funcall(parser_state_machine_t *status) {
    return PARSE_ERROR;
}

static parser_state_machine_status_t parser_state_machine_decl(parser_state_machine_t *state) {
    lex_token_t *token = NULL;
    lex_token_list_get(state->peek, token);
    if (!token) {
        return PARSE_ERROR;
    }

    switch (token->typ) {
    default:
        return PARSE_ERROR;
    }
}
static parser_state_machine_status_t
parser_state_machine_decl_struct(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t parser_state_machine_decl_var(parser_state_machine_t *state) {
    return PARSE_ERROR;
}
static parser_state_machine_status_t parser_state_machine_decl_func(parser_state_machine_t *state) {
    return PARSE_ERROR;
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
