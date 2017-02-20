#ifndef LEX_H
#define LEX_H

#define LEX_TOKEN_UNDEFINED
#define LEX_TOKEN_ERROR
#define LEX_TOKEN_EOF
#define LEX_TOKEN_END
#define LEX_TOKE_STRING
#define LEX_TOKEN_DIGIT
#define LEX_TOKEN_PLUS
#define LEX_TOKEN_MINUS
#define LEX_TOKEN_MULTI
#define LEX_TOKEN_DIV
#define LEX_TOKEN_MOD

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
    
    lex_token_list_t *start;
    lex_token_list_t *tail;

} lex_state;

typedef struct lex_token_t {
        char *sym;
        lex_typ_t typ;

        int pos;
        int len;
        int line;
}lex_token_t;

typedef struct lex_token_list_t {
        lex_token_list_t *prev;
        lex_token_t *token;
        lex_token_list_t *next;
}lex_token_list_t;

lex_state *lex_init(char *src);
int lex_state_run(lex_state *);
int lex_state_error(lex_state *state);
#endif // LEX_H
