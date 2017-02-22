#include "lex.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

#define LEX_OK 0
#define LEX_CONTINUE 1
#define LEX_ERROR 2

lex_state *lex_init(char *src) {
    lex_state *state = (lex_state *)malloc(sizeof(lex_state));
    return state;
}

int lex_state_run(lex_state *state) { return 0; }

int lex_state_error(lex_state *state) { return state->err; }

int lex_state_eof(lex_state *state){return 0;}

int lex_emit(lex_state *state, lex_token_typ_t typ) {
    return LEX_CONTINUE;
}

char lex_state_pos_incr(lex_state *state){}
char lex_state_pos_decr(lex_state *state){}

char lex_state_incr(lex_state *state) {}

char lex_state_decr(lex_state *state) {}


char lex_state_peek(lex_state *state){
    return state->src[state->pos+state->len];
}

int lex_digit(lex_state *);
int lex_ident(lex_state *);

int lex_text(lex_state *state) {
    switch(lex_state_peek(state)) {
        case '\n':
            state->line++;
        case ' ':
        case '\t':
            lex_state_pos_incr(state);
            return LEX_CONTINUE;
        case '"':
            return lex_digit(state);
        default:
            return lex_ident(state);
    }
    return LEX_ERROR;
}

#define ISDIGIT(x) x
int lex_digit(lex_state *state) {
    char c;
    while(1){
        c = lex_state_peek(state);
        if(lex_state_eof(state)) {
            return LEX_ERROR;
        }
        if(ISDIGIT(c)){
            lex_state_incr(state);
            continue;
        }else{
            lex_state_decr(state);
            break;
        }

    }
    return LEX_CONTINUE;
}

#define ISIDENT(x) x
int lex_ident(lex_state *state) {
    char c;
    while(1){
        c = lex_state_peek(state);
        if(lex_state_eof(state)){
            return LEX_ERROR;
        }
        if(ISIDENT(c) ){
            lex_state_incr(state);
            continue;
        }else{
            break;
        }

    }
    return LEX_CONTINUE;
}



int lex_string(lex_state *state) { 
    switch (lex_state_peek(state)) {
    }
    return LEX_ERROR;
}
