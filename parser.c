#include "parser.h"
#include <stdlib.h>

parser_state *parser_state_init(lex_state *lexer) {
    parser_state *state = (parser_state *)malloc(sizeof(parser_state));
    return state;
}

int parser_state_run(parser_state *state) {
    state->err    = 1;
    state->errmsg = "not yet implemented";
    return state->err;
}
const char *parser_state_error(parser_state *state) {
    if (state->err) {
        return state->errmsg;
    } else {
        return "success";
    }
}
