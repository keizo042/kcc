#include <stdint.h>
#include <stdio.h>

struct lex_token_s {
    uint64_t pos;
    uint64_t len;
    char *sym;
    uint64_t typ;
};

typedef struct lex_token_s lex_token_t;

struct lex_tokens_s {
};

typedef struct lex_token_s lex_tokens_t;

lex_tokens_t *lex(char *src)
{
    lex_tokens_t *tokens = NULL;
    return tokens;
}

void compile()
{
}
