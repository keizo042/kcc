#include "parser.h"
#include <stdlib.h>

typedef enum {
    PARSE_OK,
    PARSE_ERROR,
    PARSE_CONTINUE,
    PARSE_NODE,
    PARSE_STMT,
    PARSE_EXPR,
}parser_state_status_t;

parser_state_status_t   parser_state_machine(parser_state *state);

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
    state->err    = 1;
    state->errmsg = "not yet implemented";
    return state->err;

    parser_state_status_t rc = PARSE_CONTINUE;

    while(rc == PARSE_CONTINUE){
        rc = parser_state_machine(state);
    }
    if(rc == PARSE_ERROR){
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

parser_state_status_t   parser_state_machine(parser_state *state){
    return PARSE_ERROR;
}



///
///
///
/// *** functions for debug purpose ***
///
///
///
