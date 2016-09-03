#include <stdio.h>
#include <stdlib.h>
#include "kcc.h"
#define BUF_LEN 10240 

const char *src = "int func() {return 0; }";




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

static lex_token_t expect_test1[] = {
    {0,     3,  "int",      LEX_TOKEN_TYPE      },
    {5,     4,  "func",     LEX_TOKEN_ID        },
    {10,    1,  "(",        LEX_TOKEN_BRACKET_L },
    {11,    1,  ")",        LEX_TOKEN_BRACKET_R },
    {13,    1,  "{",        LEX_TOKEN_BRACE_R   },
    {14,    6,  "return",   LEX_TOKEN_RETURN    },
    {21,    1,  "0",        LEX_TOKEN_DIGIT     },
    {22,    1,  ";",        LEX_TOKEN_SEMICORON },
    {23,    1,  "}",        LEX_TOKEN_BRACE_R   },
    {0,     0,  "",         LEX_TOKEN_EOL       },
    {}
};

static lex_tokens_t * build_expect_to_tokens(lex_token_t *exp)
{
    lex_tokens_t *tokens = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
    lex_tokens_t *ret;
    ret = tokens;
    for(int i =0; i < sizeof(expect_test1) / sizeof(lex_tokens_t) ; i++)
    {
         tokens->token = &expect_test1[i];
         tokens->next = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
         tokens = tokens->next;
    }
    tokens->next = NULL;
    return ret;
}

static int test1_token_free(lex_tokens_t *tokens)
{
    lex_tokens_t *next = NULL;
    while(tokens->next != NULL)
    {
    next = tokens->next;
    free(tokens);
    tokens = next;
    }
    return 0;
}

int lex_test1(lex_tokens_t *l)
{
    lex_tokens_t *tokens = build_expect_to_tokens(expect_test1);

    test1_token_free(tokens);
    return 0;
}
