#ifndef __TEST_H
#define __TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kcc.h"
#define BUF_LEN 10240 


struct args_s {
};

typedef struct args_s args_t;

args_t* optparse(int argc, char **args)
{
    args_t *arg = (args_t *)malloc( sizeof(args_t));
    if(argc < 2)
    {
        free(arg);
    return NULL;
    }
    return arg;
}

lex_tokens_t * build_expect_tokens(lex_token_t *exp)
{
    lex_tokens_t *tokens = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
    lex_tokens_t *ret;
    ret = tokens;
    for(int i =0; i < sizeof(exp) / sizeof(lex_tokens_t) ; i++)
    {
         tokens->token = &exp[i];
         tokens->next = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
         tokens = tokens->next;
    }
    tokens->next = NULL;
    return ret;
}

int expect_tokens_free(lex_tokens_t *tokens)
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

#define ERROR(test,name,result) fprintf(stdout,"%s: %s: %s\n",test,name,result)
#endif
