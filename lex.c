#include "lex.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

#define LEX_OK 0
#define LEX_CONT 1
#define LEX_ERR 2

lex_state *lex_init(char *src) {
    lex_state *state = (lex_state *)malloc(sizeof(lex_state));
    return state;
}

int lex_state_run(lex_state *state) { return 0; }

int lex_state_error(lex_state *state) { return state->err; }

int lex_emit(lex_state *state, typ_t typ) {}

int lex_text(lex_state *state) {}

int lex_digit(lex_state *state) {}

int lex_ident(lex_state *state) {}



int lex_string(lex_state *state) { return }
