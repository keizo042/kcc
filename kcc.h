#ifndef _KCC_H
#define _KCC_H

#include "stdint.h"

#define ERR -1
#define DONE 0
#define CONTINUE 1

#define TEST(func,file,var,err)                     \
    do{                                             \
        if((func))                                    \
        {                                           \
            ERROR((file),(var),(err));       \
        }                                           \
    }while(0);

#define LEX_TOKEN_UNDEFINED 0
#define LEX_TOKEN_BRACE_L 1
#define LEX_TOKEN_BRACE_R 2
#define LEX_TOKEN_BRACKET_L 3
#define LEX_TOKEN_BRACKET_R 4
#define LEX_TOKEN_SEMICORON 5
#define LEX_TOKEN_RETURN 6
#define LEX_TOKEN_DIGIT 7
#define LEX_TOKEN_TYPE 8
#define LEX_TOKEN_ID 9
#define LEX_TOKEN_TOKEN 10
#define LEX_TOKEN_CORON 11
#define LEX_TOKEN_EOL 12
#define LEX_TOKEN_STR 13


#define ISDIGIT(chr) ( '0' <= chr && chr <= '9')
#define ISASCII(chr) (('a' <= chr && chr <= 'z') || ('A' <= chr && 'Z'))

struct lex_token_s;
typedef struct lex_token_s lex_token_t;

struct lex_tokens_s;
typedef struct lex_tokens_s lex_tokens_t;

struct lex_state_s;
typedef struct lex_state_s lex_state;

struct lex_token_s {
    uint64_t pos;
    uint64_t len;
    uint64_t line;
    char *sym;
    uint64_t typ;
};


struct lex_tokens_s {
    lex_token_t *token;
    lex_tokens_t *next;
};


struct lex_state_s {
    char *src;
    lex_tokens_t *head;
    lex_tokens_t *data;
    lex_tokens_t *tail;
};

struct parser_node_s;
typedef struct parser_node_s parser_node_t;

struct parser_state_s;
typedef struct parser_state_s parser_state;


void compile(const char *);
lex_state* lex(char *);
parser_state* parse(lex_state *lex);


//test utility
int lex_test_digit(char *);
int lex_test_string(char *);
int test_lex_skip_comment(char *);
int test_lex_skip_until(char *,char);
int test_lex_token_new(lex_token_t *);
int test_lex_token(char *);

#endif // _KCC_H
