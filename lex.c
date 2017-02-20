#include "lex.h"
#include <stdlib.h>


lex_state* lex_init(char *src){
    lex_state *state = (lex_state*)malloc(sizeof(lex_state));
    return state;
}

int lex_state_run(lex_state* state){
    return 0;
}

int lex_state_error(lex_state* state){
    return state->err;
}
