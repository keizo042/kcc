#ifndef LEX_H
#define LEX_H

typedef enum {
    LEX_TOKEN_UNDEFINED,
    LEX_TOKEN_ERROR,
    LEX_TOKEN_EOF,
    LEX_TOKEN_STRING,
    LEX_TOKEN_DIGIT,
    LEX_TOKEN_PLUS,
    LEX_TOKEN_MINUS,
    LEX_TOKEN_MULTI,
    LEX_TOKEN_DIV,
    LEX_TOKEN_MOD,
    LEX_TOKEN_END,
    LEX_TOKEN_KEYWORD,
    LEX_TOKEN_PAREN_L,
    LEX_TOKEN_PAREN_R,
    LEX_TOKEN_BRACKET_L,
    LEX_TOKEN_BRACKET_R,
    LEX_TOKEN_BRACE_L,
    LEX_TOKEN_BRACE_R,
    LEX_TOKEN_TYPE,
    LEX_TOKEN_DOT,
    LEX_TOKEN_PTR,
} lex_token_typ_t;

typedef int lex_typ_t;

struct lex_token_t;
typedef struct lex_token_t lex_token_t;

struct lex_token_list_t;
typedef struct lex_token_list_t lex_token_list_t;

struct lex_state;
typedef struct lex_state lex_state;

typedef struct lex_state {
    char *src;
    int pos;
    int width;
    int len;
    int line;
    int err;
    int errmsg_len;
    char *errmsg;

    lex_token_list_t *start;
    lex_token_list_t *tail;

} lex_state;

typedef struct lex_token_t {
    char *sym;
    lex_typ_t typ;

    int pos;
    int len;
    int line;
} lex_token_t;

typedef struct lex_token_list_t {
    lex_token_list_t *prev;
    lex_token_t *token;
    lex_token_list_t *next;
} lex_token_list_t;

lex_state *lex_state_init(char *src);
int lex_state_run(lex_state *);
const char *lex_state_error(lex_state *state);
#endif // LEX_H
