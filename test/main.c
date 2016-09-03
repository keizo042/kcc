#include <stdio.h>
#include <stdlib.h>
#include "kcc.h"
#define BUF_LEN 10240 

const char *src = "int func() {return 0; }";


lex_token_t expect[] = {
    {0,     3,  "int",      LEX_TOKEN_TYPE      },
    {5,     4,  "func",     LEX_TOKEN_ID        },
    {10,    1,  "(",        LEX_TOKEN_BRACKET_L },
    {11,    1,  ")",        LEX_TOKEN_BRACKET_R },
    {13,    1,  "{",        LEX_TOKEN_BRACE_R   },
    {14,    6,  "return",   LEX_TOKEN_RETURN    },
    {21,    1,  "0",        LEX_TOKEN_DIGIT     },
    {22,    1,  ";",        LEX_TOKEN_SEMICORON },
    {23,    1,  "}",        LEX_TOKEN_BRACE_R   },
    {}
};

lex_tokens_t * build_expect_to_tokens(lex_token_t **exp)
{
    lex_tokens_t *tokens = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
    lex_tokens_t *ret;
    ret = tokens;
    for(int i =0; exp[i] != NULL; i++)
    {
         tokens->token = &expect[i];
         tokens->next = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
         tokens = tokens->next;
    }
    return ret;
}


int lex_test1(lex_tokens_t *l);


int
main(int argc, char* argv[]) {
    
    FILE *fp;
    char buf[BUF_LEN];
    lex_state *l;
    l = lex(buf);
    if(l == NULL)
    {
        printf("lex return null ptr\n");
        goto fail;
    }
    if(lex_test1(l->head))
    {
        printf("lex_test1 fail\n");
        goto fail;
    }
        

sucess:
    printf("test pass!\n");
    return 0;
    
fail:
    printf("test fail...\n");
    return -1;
}


int lex_test1(lex_tokens_t *l)
{
    return -1;
}
