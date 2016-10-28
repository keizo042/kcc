#include "lex.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ISDIGIT(x) (('0' <= (x)) && ((x) <= '0'))
#define ISASCII(x) ((0 <= (x)) && ((x) <= 255))
#define ISCHAR(x) (('a' <= (x)) && ((x) <= 'z')) || (('A' <= (x) && (x) <= 'Z'))
#define ISIDENT(x) (ISDIGIT(x) || ISCHAR(x))

static char lex_state_next(lex_state *state);
static char lex_state_peek(lex_state *state);
static char lex_state_pook(lex_state *state);
static lex_tok_t *lex_token_new(char *sym, uint64_t len, tok_typ_t typ, uint64_t line);
static void lex_tok_free(lex_tok_t *token);
char *lex_tok_sym(lex_tok_t *token);
char *lex_tok_typ_str(lex_tok_t *token);
lex_tok_stream_t *lex_tok_stream_new();
lex_state *lex_state_open(char *src);
static int lex_emit(lex_state *state, tok_typ_t t);


struct lex_tok_s {
    char *sym;
    tok_typ_t typ;
    uint64_t pos;
    uint64_t line;
};

struct lex_tok_stream_s {
    lex_tok_t *token;
    struct lex_tok_stream_s *next;
};


static lex_tok_t *lex_token_new(char *sym, uint64_t len, tok_typ_t typ, uint64_t line) {
    lex_tok_t *token = (lex_tok_t *)malloc(sizeof(lex_tok_t));
    token->sym       = (char *)malloc(sizeof(char) * len + 1);

    strncpy(token->sym, sym, len);
    token->typ  = typ;
    token->line = line;
    return token;
}

static void lex_tok_free(lex_tok_t *token) {
    if (token->sym != NULL) {
        free(token->sym);
    }
    if (token != NULL) {
        free(token);
    }
}

char *lex_tok_sym(lex_tok_t *token) { return token->sym; }
char *lex_tok_typ_str(lex_tok_t *token) {
    if (token == NULL) {
        return " ";
    }
    switch (token->typ) {
    case LEX_TOKEN_END:
        return "LEX_TOKEN_END";
    case LEX_TOKEN_DIGIT:
        return "LEX_TOKEN_DIGIT";
    case LEX_TOKEN_STRING:
        return "LEX_TOKEN_STRING";
    case LEX_TOKEN_BRACE_L:
        return "LEX_TOKEN_BRACE_L";
    case LEX_TOKEN_BRACE_R:
        return "LEX_TOKEN_BRACE_R";
    case LEX_TOKEN_BRACKET_L:
        return "LEX_TOKEN_BRACKET_L";
    case LEX_TOKEN_BRACKET_R:
        return "LEX_TOKEN_BRACKET_R";
    case LEX_TOKEN_CONNMA:
        return "LEX_TOKEN_CONNMA";
    case LEX_TOKEN_CORON:
        return "LEX_TOKEN_CORON";
    case LEX_TOKEN_EQ:
        return "LEX_TOKEN_EQ";
    case LEX_TOKEN_LESS:
        return "LEX_TOKEN_LESS";
    case LEX_TOKEN_MORE:
        return "LEX_TOKEN_MORE";
    case LEX_TOKEN_IF:
        return "LEX_TOKEN_IF";
    case LEX_TOKEN_ELSE:
        return "LEX_TOKEN_ELSE";
    case LEX_TOKEN_WHILE:
        return "LEX_TOKEN_WHILE";
    case LEX_TOKEN_SWITCH:
        return "LEX_TOKEN_SWITCH";
    case LEX_TOKEN_CASE:
        return "LEX_TOKEN_CASE";
    case LEX_TOKEN_GOTO:
        return "LEX_TOKEN_GOTO";
    case LEX_TOKEN_KEYWORD:
        return "LEX_TOKEN_KEYWORD";
    case LEX_TOKEN_IDENT:
        return "LEX_TOKEN_IDENT";
    case LEX_TOKEN_PLUS:
        return "LEX_TOKEN_PLUS";
    case LEX_TOKEN_MINUS:
        return "LEX_TOKEN_MINUS";
    case LEX_TOKEN_MULTI:
        return "LEX_TOKEN_MULTI";
    case LEX_TOKEN_DIV:
        return "LEX_TOKEN_DIV";
    case LEX_TOKEN_SQUARE_BRACKET_L:
        return "LEX_TOKEN_SQUARE_BRACKET_L";
    case LEX_TOKEN_SQUARE_BRACKET_R:
        return "LEX_TOKEN_SQUARE_BRACKET_R";
    case LEX_TOKEN_EOF:
        return "LEX_TOKEN_EOF";
    case LEX_TOKEN_TYPE:
        return "LEX_TOKEN_TYPE";
    case LEX_TOKEN_QUESTION:
        return "LEX_TOKEN_QURESTION";
    case LEX_TOKEN_EXCLAMATION:
        return "LEX_TOKEN_EXCLAMATION";
    case LEX_TOKEN_RETURN:
        return "LEX_TOKEN_RETURN";
    default:
        return "unkown";
    }
}

lex_tok_stream_t *lex_tok_stream_new() {
    lex_tok_stream_t *stream = malloc(sizeof(lex_tok_stream_t));
    stream->next             = NULL;
    return stream;
}


lex_state *lex_state_open(char *src) {
    lex_state *state = (lex_state *)malloc(sizeof(lex_state));
    state->src       = src;
    state->start     = state->src;
    state->pos       = 0;
    state->len       = 0;
    state->line      = 0;
    state->head      = NULL;
    state->stream    = lex_tok_stream_new();
    return state;
}


static char lex_state_pook(lex_state *state) {
    if (state->start == state->start + state->pos + state->len - 1) {
        state->err = 1;
        return '\0';
    }
    return *(state->start + state->pos + state->len - 1);
}

static char lex_state_peek(lex_state *state) { return *(state->start + state->pos + state->len); }
static char lex_state_next(lex_state *state) {
    return *(state->start + state->pos + state->len + 1);
}


// state transmisition tables

static int lex_emit(lex_state *state, tok_typ_t t) {
    lex_tok_t *token     = lex_token_new(state->start + state->pos, state->len, t, state->line);
    state->stream->token = token;

    state->stream->next = lex_tok_stream_new();
    state->stream       = state->stream->next;

    state->start = state->start + state->pos + state->len;
    state->pos   = 0;
    state->len   = 0;

    if (t == LEX_TOKEN_EOF) {
        return LEX_FIN;
    } else {
        return LEX_CONTINUE;
    }
}

static int lex_string(lex_state *state) {
    if (lex_state_peek(state) != '"') {
        return LEX_ERR;
    }
    state->pos++;
    while (lex_state_next(state) != '"' ||
           (lex_state_peek(state) != '\\' && lex_state_pook(state) != '\\')) {
        if (lex_state_next(state) == '\0') {
            return LEX_ERR;
        }
        state->len++;
    }
    lex_emit(state, LEX_TOKEN_STRING);
    state->start++;

    return LEX_CONTINUE;
}

static int lex_digit(lex_state *state) {
    if (!ISDIGIT(lex_state_peek(state))) {
        return LEX_ERR;
    }
    state->len++;

    while (ISDIGIT(lex_state_peek(state))) {
        state->len++;
    }
    if (lex_state_peek(state) != '.') {
        state->len--;
        lex_emit(state, LEX_TOKEN_DIGIT);
        return LEX_CONTINUE;
    }

    while (ISDIGIT(lex_state_peek(state))) {
        state->len++;
    }
    lex_emit(state, LEX_TOKEN_DIGIT);

    return LEX_CONTINUE;
}


static int lex_identity(lex_state *state) {
    int len;
    if (!ISCHAR(lex_state_peek(state))) {
        return LEX_ERR;
    }
    while (ISIDENT(lex_state_peek(state))) {
        state->len++;
    }
    return lex_emit(state, LEX_TOKEN_IDENT);
}

static int lex_text(lex_state *state) {

    while (1) {
        switch (state->start[state->pos]) {
        case '\0':
            return lex_emit(state, LEX_TOKEN_EOF);
        case ' ':
            state->pos++;
            return LEX_CONTINUE;
        case '\n':
            state->pos++;
            state->line++;
            return LEX_CONTINUE;
        case ':':
            state->len++;
            return lex_emit(state, LEX_TOKEN_CORON);
        case ',':
            state->len++;
            return lex_emit(state, LEX_TOKEN_CONNMA);
        case '{':
            state->len++;
            return lex_emit(state, LEX_TOKEN_BRACE_L);
        case '}':
            state->len++;
            return lex_emit(state, LEX_TOKEN_BRACE_R);
        case '(':
            state->len++;
            return lex_emit(state, LEX_TOKEN_BRACKET_L);
        case ')':
            state->len++;
            return lex_emit(state, LEX_TOKEN_BRACKET_R);
        case '<':
            state->len++;
            return lex_emit(state, LEX_TOKEN_LESS);
        case '>':
            state->len++;
            return lex_emit(state, LEX_TOKEN_MORE);
        case '/':
            if (state->start[state->pos + 1] == '/') {
                while (state->start[state->pos] != '\n') {
                    state->pos++;
                }
            }
            if (state->start[state->pos + 1] == '*') {
                state->pos = state->pos + 2;
                while (1) {
                    if (state->start[state->pos - 1] == '*' && state->start[state->pos] == '/') {
                        state->pos++;
                        return LEX_CONTINUE;
                    }
                    state->pos++;
                }
            }
            state->len++;
            return lex_emit(state, LEX_TOKEN_DIV);
        case '+':
            state->len++;
            return lex_emit(state, LEX_TOKEN_PLUS);
        case '-':
            state->len++;
            return lex_emit(state, LEX_TOKEN_MINUS);
        case '*':
            state->len++;
            return lex_emit(state, LEX_TOKEN_MULTI);
        case '#':
            while (state->start[state->pos] != '\n') {
                state->pos++;
            }
            return LEX_CONTINUE;
        default:
            return lex_identity(state);
        }
    }
}

lex_state *lex(char *src) {
    int s            = LEX_ERR;
    lex_state *state = lex_state_open(src);
    state->stream    = lex_tok_stream_new();
    state->head      = state->stream;


    while (s == LEX_CONTINUE) {
        s = lex_text(state);
    }

    if (s == LEX_ERR) {
        return NULL;
    }
    return state;
}



int lex_tok_pp(lex_tok_t *token) {
    printf("%s:%s", lex_tok_typ_str(token), lex_tok_sym(token));
    return 0;
}

int lex_tok_stream_pp(lex_tok_stream_t *stream) {
    if (stream == NULL) {
        return 0;
    }
    lex_tok_pp(stream->token);
    printf(", ");
    lex_tok_stream_pp(stream->next);
    return 0;
}
