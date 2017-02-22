#include "lex.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
    LEX_OK,
    LEX_CONTINUE,
    LEX_ERROR,
} lex_state_status_t;

lex_state_status_t lex_text(lex_state *);
lex_state_status_t lex_string(lex_state *);
lex_state_status_t lex_ident(lex_state *);
lex_state_status_t lex_digit(lex_state *);

lex_token_t *lex_token_init(char *sym, lex_token_typ_t typ, int pos, int line) {
    lex_token_t *token = malloc(sizeof(lex_token_t));
    token->sym         = sym;
    token->typ         = typ;
    token->pos         = pos;
    token->line        = line;

    return token;
}


lex_token_list_t *lex_token_list_init() {
    lex_token_list_t *list = (lex_token_list_t *)malloc(sizeof(lex_token_list_t));
    list->prev             = NULL;
    list->token            = NULL;
    list->next             = NULL;
    return list;
}

lex_token_list_t *lex_token_list_update(lex_token_list_t *list, lex_token_t *token) {
    lex_token_list_t *next_entry = lex_token_list_init();
    list->token                  = token;

    next_entry->prev = list;
    list->next       = next_entry;
    return next_entry;
}

int lex_token_list_succ(lex_token_list_t *list, lex_token_t *token) {
    lex_token_list_t *t = NULL;

    token = list->token;
    t     = list;
    list  = list->next;
    return 0;
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
    state->tail       = state->start;
    return state;
}

int lex_state_run(lex_state *state) {
    lex_state_status_t rc = LEX_CONTINUE;

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

int lex_state_print(lex_state *state) {
    lex_token_list_t *p;
    char *buf;

    for (p = state->start; p != NULL; p = p->next) {
        char *buf = lex_token2string(p->token);
        if (buf == NULL) {
            return 1;
        }
        printf("%s\n", buf);
    }
    return 0;
}

//
//
// * internal api *
//
//


int lex_state_eof(lex_state *state) { return state->src[state->pos + state->len] == EOF; }

lex_state_status_t lex_emit(lex_state *state, lex_token_typ_t typ) {
    char *sym               = (char *)malloc(sizeof(char) * state->len + 1);
    lex_token_list_t *entry = NULL;
    sym[state->len]         = '\0';
    strncpy(sym, state->src + state->pos, state->len);

    lex_token_t *token = lex_token_init(sym, typ, state->pos, state->line);
    state->pos         = state->pos + state->len;
    state->len         = 0;
    entry              = lex_token_list_update(state->tail, token);
    state->tail        = entry;
    return LEX_CONTINUE;
}

char lex_state_pos_incr(lex_state *state) {
    state->pos++;
    return state->src[state->pos + state->len];
}
char lex_state_pos_decr(lex_state *state) {
    state->pos--;
    if (state->pos <= 0) {
        char *msg         = "invalid negative access to src code";
        state->err        = 1;
        state->errmsg_len = strlen(msg);
        state->errmsg     = (char *)malloc(state->errmsg_len);
        return EOF;
    }
    return state->src[state->pos + state->len];
}

char lex_state_incr(lex_state *state) {
    state->len++;
    return state->src[state->pos + state->len];
}

char lex_state_decr(lex_state *state) {
    state->len--;
    if (state->pos <= 0) {
        char *msg         = "invalid negative access to src code";
        state->err        = 1;
        state->errmsg_len = strlen(msg);
        state->errmsg     = (char *)malloc(state->errmsg_len);
        return EOF;
    }
    return state->src[state->pos + state->len];
}


char lex_state_peek(lex_state *state) { return state->src[state->pos + state->len]; }


lex_state_status_t lex_text(lex_state *state) {
    switch (lex_state_peek(state)) {
    case '\0':
        lex_emit(state, LEX_TOKEN_EOF);
        return LEX_OK;
    case '\n':
        state->line++;
    case ' ':
    case '\t':
        lex_state_pos_incr(state);
        return LEX_CONTINUE;
    case ';':
        lex_state_incr(state);
        return lex_emit(state, LEX_TOKEN_END);
    case '+':
        lex_state_incr(state);
        return lex_emit(state, LEX_TOKEN_PLUS);
    case '-':
        lex_state_incr(state);
        return lex_emit(state, LEX_TOKEN_MINUS);
    case '/':
        lex_state_incr(state);
        return lex_emit(state, LEX_TOKEN_DIV);
    case '"':
        return lex_string(state);
    default:
        return lex_ident(state);
    }
    return LEX_ERROR;
}

#define ISDIGIT(x) ('0' <= (x) && (x) <= '9')
#define ISCHAR(x) ('a' <= (x) && (x) <= 'z') || ('A' <= (x) && (x) <= 'Z')
#define ISIDENT(x) ISDIGIT(x) || ISCHAR(x)

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
            break;
        }
    }
    return lex_emit(state, LEX_TOKEN_DIGIT);
}

lex_state_status_t lex_ident(lex_state *state) {
    char c;
    c = lex_state_peek(state);
    if (ISDIGIT(c)) {
        return lex_digit(state);
    }

    while (1) {
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
    return lex_emit(state, LEX_TOKEN_DIGIT);
}


lex_state_status_t lex_string(lex_state *state) {
    char c;
    if (lex_state_peek(state) != '"') {
        return LEX_ERROR;
    }
    while (ISCHAR(c)) {
        c = lex_state_incr(state);
    }
    if (lex_state_peek(state) != '"') {
        return LEX_ERROR;
    }
    return lex_emit(state, LEX_TOKEN_STRING);
}



//
//
//
// **** functions for debug purpose ***
//
//
//

char *lex_token_typ2string(lex_token_typ_t typ) {
    switch (typ) {
    case LEX_TOKEN_UNDEFINED:
        return "UNDEFINED";
    case LEX_TOKEN_ERROR:
        return "ERROR";
    case LEX_TOKEN_EOF:
        return "EOF";
    case LEX_TOKEN_STRING:
        return "STRING";
    case LEX_TOKEN_DIGIT:
        return "DIGIT";
    case LEX_TOKEN_PLUS:
        return "PLUS";
    case LEX_TOKEN_MINUS:
        return "MINUS";
    case LEX_TOKEN_DIV:
        return "DIV";
    case LEX_TOKEN_MOD:
        return "MOD";
    case LEX_TOKEN_END:
        return "END";
    case LEX_TOKEN_KEYWORD:
        return "KEYWORD";
    case LEX_TOKEN_PAREN_L:
        return "PAREN_L";
    case LEX_TOKEN_PAREN_R:
        return "PAREN_R";
    case LEX_TOKEN_BRACKET_L:
        return "BRACEKT_L";
    case LEX_TOKEN_BRACKET_R:
        return "BRACKET_R";
    case LEX_TOKEN_BRACE_L:
        return "BRACE_L";
    case LEX_TOKEN_BRACE_R:
        return "BRACE_R";
    case LEX_TOKEN_TYPE:
        return "TYPE";
    case LEX_TOKEN_DOT:
        return "DOT";
    case LEX_TOKEN_ASTRISK:
        return "ASTRISK";
    default:
        return NULL;
    }
}

char *lex_token2string(lex_token_t *token) {
    if (token == NULL) {
        return NULL;
    }
    char *buf = (char *)malloc(256);
    sprintf(buf, "{%d:%s, pos:%d,line:%d}", token->typ, token->sym, token->pos, token->line);
    return buf;
}
