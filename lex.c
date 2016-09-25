#include "lex.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define get_token_state(state) (state)->stream->token
#define ISDIGIT(x) (('0' <= (x)) && ((x) <= '0'))
#define ISASCII(x) ((0 <= (x)) && ((x) <= 255))
#define ISCHAR(x) (('a' <= (x)) && ((x) <= 'z')) || (('A' <= (x) && (x) <= 'Z'))
#define ISIDENT(x) (ISDIGIT(x) || ISCHAR(x))
#define lex_token_new_state(state, t)                                                              \
    lex_token_new((state)->src + (state)->pos, (state)->len, (t), (state)->pos, (state)->line)


// token definitions
typedef uint64_t tok_typ_t;

struct lex_tok_s {
    char *sym;
    tok_typ_t typ;
    uint64_t pos;
    uint64_t line;
};

typedef struct lex_tok_s lex_tok_t;

static lex_tok_t *lex_token_new(char *sym, uint64_t len, tok_typ_t typ, uint64_t pos,
                                uint64_t line) {
    lex_tok_t *token = (lex_tok_t *)malloc(sizeof(lex_tok_t));
    token->sym       = (char *)malloc(sizeof(char) * len + 1);

    strncpy(token->sym, sym, len);
    token->typ  = typ;
    token->pos  = pos;
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

struct lex_tok_stream_s {
    lex_tok_t *token;
    struct lex_tok_stream_s *prev;
    struct lex_tok_stream_s *next;
};

typedef struct lex_tok_stream_s lex_tok_stream_t;

struct lex_state_s {
    char *src;
    uint64_t pos;
    uint64_t len;
    uint64_t line;
    lex_tok_stream_t *head;
    lex_tok_stream_t *stream;
};



static const char *typs[] = {"int", "float", "double", "char", "uint32_t", "uint64_t", ""};

typedef struct typs_s {
    char *sym;
    tok_typ_t typ;
} typs_t;

static const typs_t keywords[] = {{"if", LEX_TOKEN_IF},
                                  {"while", LEX_TOKEN_WHILE},
                                  {"else", LEX_TOKEN_ELSE},
                                  {"switch", LEX_TOKEN_SWITCH},
                                  {"case", LEX_TOKEN_CASE},
                                  {"return", LEX_TOKEN_RETURN},
                                  {NULL}};

static const char *specifics[] = {"struct", "union", ""};

static const char *qualified[] = {"typedef", "static", "const", ""};


// state transmisition tables

static int lex_emit(lex_state *state, tok_typ_t t) {
    lex_tok_t *token         = lex_token_new_state(state, t);
    lex_tok_stream_t *stream = (lex_tok_stream_t *)malloc(sizeof(lex_tok_stream_t));
    stream->next             = NULL;

    state->stream->token = token;

    state->stream->next = stream;
    stream->prev        = state->stream;

    state->stream = state->stream->next;
    if (t == LEX_TOKEN_EOF) {
        return LEX_FIN;
    } else {
        return LEX_CONTINUE;
    }
}



static int lex_string(lex_state *state) {
    if (state->src[state->pos] != '"') {
        return LEX_ERR;
    }
    state->pos++;
    while (state->src[state->pos + state->len] != '"') {
        if (state->src[state->pos + state->len] == '\0') {
            return LEX_ERR;
        }
        state->len++;
    }
    state->pos--;
    lex_emit(state, LEX_TOKEN_STRING);
    state->pos = state->pos + 2;

    return LEX_CONTINUE;
}

static int lex_digit(lex_state *state) {
    if (!ISDIGIT(state->src[state->pos])) {
        return LEX_ERR;
    }
    while (ISDIGIT(state->src[state->pos + state->len])) {
        state->len++;
    }
    if (state->src[state->pos + state->len] != '.') {
        lex_emit(state, LEX_TOKEN_DIGIT);
        return LEX_CONTINUE;
    }
    while (ISDIGIT(state->src[state->pos + state->len])) {
        state->len++;
    }
    lex_emit(state, LEX_TOKEN_DIGIT);

    return LEX_CONTINUE;
}

static inline int check_ident_is_type(lex_state *state) {
    int i, len;
    for (i = 0; typs[i] != '\0'; i++) {
        if (strncmp(state->src + state->pos, typs[i], len = strlen(typs[i])) == 0) {
            state->len = len;
            return 1;
        }
    }
    return 0;
}

static inline int check_ident_is_qualified(lex_state *state) {
    int i, len;
    for (i = 0; qualified[i] != '\0'; i++) {
        if (strncmp(state->src + state->pos, qualified[i], len = strlen(qualified[i])) == 0) {
            state->len = len;
            return 1;
        }
    }
    return 0;
}

static int lex_identity(lex_state *state) {
    int len;
    if (!ISCHAR(state->src[state->pos + state->len])) {
        return LEX_ERR;
    }
    if (check_ident_is_type(state)) {
        return lex_emit(state, LEX_TOKEN_TYPE);
    }
    if (check_ident_is_qualified(state)) {
        return lex_emit(state, LEX_TOKEN_KEYWORD);
    }

    for (int i = 0; keywords[i].sym != NULL; i++) {
        if (strncmp(state->src + state->pos, keywords[i].sym, len = strlen(keywords[i].sym)) == 0) {
            state->len = len;
            return lex_emit(state, keywords[i].typ);
        }
    }
    while (ISIDENT(state->src[state->pos + state->len])) {
        state->len++;
    }
    return lex_emit(state, LEX_TOKEN_IDENT);
}

static int lex_text(lex_state *state) {

    while (1) {
        switch (state->src[state->pos]) {
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
            if (state->src[state->pos + 1] == '/') {
                while (state->src[state->pos] != '\n') {
                    state->pos++;
                }
            }
            if (state->src[state->pos + 1] == '*') {
                state->pos = state->pos + 2;
                while (1) {
                    if (state->src[state->pos - 1] == '*' && state->src[state->pos] == '/') {
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
            while (state->src[state->pos] != '\n') {
                state->pos++;
            }
            return LEX_CONTINUE;
        default:
            return lex_identity(state);
        }
    }
}

lex_state *lex(char *src) {
    int s;
    lex_state *state;


    while (s == LEX_CONTINUE) {
        s = lex_text(state);
    }

    if (s == LEX_ERR) {
        return NULL;
    }
    return state;
}



/*
   *
   * test functions
   *
   *
*/
#ifdef __DEBUG

int test1(char *src){
    return 1;
}
#endif
