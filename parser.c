#include "parser.h"
#include "lex.h"
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

static parser_state_status_t state_machine_binop(parser_state *);  // + or -
static parser_state_status_t state_machine_binop2(parser_state *); // * or /
static parser_state_status_t state_machine_uniop(parser_state *);  //

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
