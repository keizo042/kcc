#include "lex.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
    LEX_OK,
    LEX_CONTINUE,
    LEX_ERROR,
} lex_state_status_t;

lex_state_status_t lex_text(lex_state*);
lex_state_status_t lex_string(lex_state*);
lex_state_status_t lex_ident(lex_state*);
lex_state_status_t lex_digit(lex_state*);

lex_token_t *lex_token_init(char *sym, lex_token_typ_t typ, int pos, int line) {
    lex_token_t *token = malloc(sizeof(lex_token_t));
    int n              = strlen(sym);

    token->sym = malloc(n + 1);
    strncpy(token->sym, sym, n);
    token->typ = typ;
    token->pos = pos;
    token->line = line;

    return token;
}


lex_token_list_t *lex_token_list_init() {
    lex_token_list_t *list = (lex_token_list_t *)malloc(sizeof(lex_token_list_t));
    list->prev             = NULL;
    list->token            = NULL;
    list->next             = NULL;
    return list;
}

lex_token_list_t* lex_token_list_update(lex_token_list_t *list, lex_token_t *token) {
    lex_token_list_t *new_entry = lex_token_list_init();
    new_entry->prev             = list;
    new_entry->token            = token;
    return new_entry;
}

lex_state *lex_state_init(char *src) {
    lex_state *state  = (lex_state *)malloc(sizeof(lex_state));
    state->src        = src;
    state->pos        = 0;
    state->width      = 0;
    state->len        = 0;
    state->line       = 0;
    state->err        = 0;
    state->errmsg_len = 0;
    state->errmsg     = NULL;
    state->start      = lex_token_list_init();
    return state;
}

int lex_state_run(lex_state *state) {
    lex_state_status_t rc;

    while (rc == LEX_CONTINUE) {
        rc = lex_text(state);
    }
    if (rc == LEX_ERROR) {
        return 1;
    }
    return 0;
}

const char *lex_state_error(lex_state *state) {
    if (state->err) {
        return state->errmsg;
    }
    return "";
}

int lex_state_eof(lex_state *state) { 
    return state->src[state->pos+ state->len] == EOF;
}

lex_state_status_t lex_emit(lex_state *state, lex_token_typ_t typ) { return LEX_CONTINUE; }

char lex_state_pos_incr(lex_state *state) {
    state->pos++;
    return state->src[state->pos+ state->len];
}
char lex_state_pos_decr(lex_state *state) {
    state->pos--;
    if(state->pos <= 0){
        char *msg = "invalid negative access to src code";
        state->err =1;
        state->errmsg_len = strlen(msg);
        state->errmsg = (char *)malloc(state->errmsg_len);
        return EOF;
    }
    return state->src[state->pos + state->len];
}

char lex_state_incr(lex_state *state) {
    state->len++;
    return state->src[state->pos + state->len];
}

char lex_state_decr(lex_state *state) {
    state->len-- ;
    if(state->pos <= 0){
        char *msg = "invalid negative access to src code";
        state->err =1;
        state->errmsg_len = strlen(msg);
        state->errmsg = (char *)malloc(state->errmsg_len);
        return EOF;
    }
    return state->src[state->pos + state->len];
}


char lex_state_peek(lex_state *state) { return state->src[state->pos + state->len]; }


lex_state_status_t lex_text(lex_state *state) {
    switch (lex_state_peek(state)) {
    case '\n':
        state->line++;
    case ' ':
    case '\t':
        lex_state_pos_incr(state);
        return LEX_CONTINUE;
    case '"':
        return lex_string(state);
    default:
        return lex_ident(state);
    }
    return LEX_ERROR;
}

#define ISDIGIT(x) x
lex_state_status_t lex_digit(lex_state *state) {
    char c;
    while (1) {
        c = lex_state_peek(state);
        if (lex_state_eof(state)) {
            return LEX_ERROR;
        }
        if (ISDIGIT(c)) {
            lex_state_incr(state);
            continue;
        } else {
            lex_state_decr(state);
            break;
        }
    }
    return LEX_CONTINUE;
}

#define ISIDENT(x) x
lex_state_status_t lex_ident(lex_state *state) {
    char c;
    while (1) {
        c = lex_state_peek(state);
        if (lex_state_eof(state)) {
            return LEX_ERROR;
        }
        if (ISIDENT(c)) {
            lex_state_incr(state);
            continue;
        } else {
            break;
        }
    }
    return LEX_CONTINUE;
}



lex_state_status_t lex_string(lex_state *state) {
    switch (lex_state_peek(state)) {}
    return LEX_ERROR;
}
