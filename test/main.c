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

char *test1_code_function = "int func() {return 0; }";
char *test2_code_comment = "// yuyushiki is awesome. //";
char *test2_code_comments =  "/* Domo Geek=san.\nNinja Slayer desu\n*/";
char *test3_code_pragma_digit = "#define PRAGMA 1";
char *test3_code_pragma_str = "#define STR \"string\" ";


static int lex_test1(lex_tokens_t *l);
static int lex_test2_comment(lex_tokens_t *l);
static int lex_test3_pragma_digit(lex_tokens_t *l);
static int lex_test3_pragma_str(lex_tokens_t *tokens);


int
main(int argc, char* argv[]) {
    
    FILE *fp;
    int flag = 0;
    lex_state *l1, 
              *l2;
    lex_state *l3digit,
              *l3str;

    l1 = lex(test1_code_function);
    if(l1 == NULL)
    {
        flag = 1;
        printf("test1: lex return null ptr\n");
        goto test1_end;
    }else
    {
        printf("test1:lex pass...\n");
    }

    if(lex_test1(l1->head))
    {
        flag = 1;
        printf("lex_test1 fail\n");
        goto test1_end;
    }else
    {
        printf("test1:\n");
    }
test1_end:

    l2 = lex(test2_code_comment);
    if(l2 == NULL)
    {
        flag = 1;
        printf("test2: lex return null ptr\n");
        goto test2_end;
    }else
    {
        printf("test2:lex pass..\n");
    }

    if(lex_test2_comment(l2->head))
    {
        flag = 1;
        printf("test2: lex_test2 fail\n");
        goto test2_end;
    }else
    {
        printf("test2:\n");
    }
test2_end:


    l3digit = lex(test3_code_pragma_digit);
    if(lex_test3_pragma_digit(l3digit->head) != 0)
    {
        flag =1;
        printf("test3: fail\n");
        goto test3_end;
    }else
    {
    }

    l3str = lex(test3_code_pragma_str);
    if(lex_test3_pragma_str(l3str->head) != 0)
    {
        printf("test3: fail");
        flag = 1;
        goto test3_end;
    }else
    {
    }
test3_end:
        

    if(flag == 0)
    {
    printf("test pass!\n");
    return 0;
    }else
    {
    printf("test fail...\n");
    return -1;
    }
    
}


static lex_tokens_t * build_expect_tokens(lex_token_t *exp)
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

static int expect_tokens_free(lex_tokens_t *tokens)
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

static lex_token_t test1_expect_tokens[] = {
    { .pos = 0,     .len = 3,   .line = 0,  "int",      LEX_TOKEN_TYPE      },
    { .pos = 5,     .len = 4,   .line = 0,  "func",     LEX_TOKEN_ID        },
    { .pos = 10,    .len = 1,   .line = 0,  "(",        LEX_TOKEN_BRACKET_L },
    { .pos = 11,    .len = 1,   .line = 0,  ")",        LEX_TOKEN_BRACKET_R },
    { .pos = 13,    .len = 1,   .line = 0,  "{",        LEX_TOKEN_BRACE_R   },
    { .pos = 14,    .len = 6,   .line = 0,  "return",   LEX_TOKEN_RETURN    },
    { .pos = 21,    .len = 1,   .line = 0,  "0",        LEX_TOKEN_DIGIT     },
    { .pos = 22,    .len = 1,   .line = 0,  ";",        LEX_TOKEN_SEMICORON },
    { .pos = 23,    .len = 1,   .line = 0,  "}",        LEX_TOKEN_BRACE_R   },
    { .pos = 0,     .len = 0,   .line = 0,  "",         LEX_TOKEN_EOL       },
    {}
};

int lex_test1(lex_tokens_t *tokens)
{
    lex_tokens_t *expect = build_expect_tokens(test1_expect_tokens);
    if(tokens == NULL)
    {
        expect_tokens_free(expect);
        return -1;
    }
    while(0)
    {
        if(tokens == NULL)
        {
            return -2;
        
        }
    }

    expect_tokens_free(expect);
    return 0;

}

static lex_token_t test2_expect_tokens[] = {
    {.typ = LEX_TOKEN_EOL},
    {}
    
};


static int lex_test2_comment(lex_tokens_t *tokens)
{
    lex_tokens_t *expect =  build_expect_tokens(test2_expect_tokens);
    if( tokens == NULL)
    {
        return -1;
    }

    lex_tokens_t *e = expect,
                *t = tokens;
    while(t != NULL)
    {
        if(e->token->pos !=  t->token->pos)
        {
            return -2;
        }

        if(e->token->len != t->token->len)
        {
            return -3;
        }

        if(strcmp(e->token->sym, t->token->sym) != 0)
        {
            return -4;
        }
        
        if(e->token->line != t->token->line)
        {
            return -5;
        }
        if(e->token->typ != e->token->typ)
        {
            return -6;
        }
        e = e->next;
        t = t->next;

    }
    expect_tokens_free(expect);
    return 0;
}

static lex_token_t test2_comments_expect_tokens[] = {
    {.typ = LEX_TOKEN_EOL}
};

static int lex_test2_comments(lex_tokens_t *tokens)
{
    lex_tokens_t *expect = build_expect_tokens(test2_comments_expect_tokens);
    expect_tokens_free(expect);
    return -1;
}

static lex_token_t test3_pragma_digit_expect_tokens[] = {
    {.typ = LEX_TOKEN_EOL},
    {}
};

static int lex_test3_pragma_digit(lex_tokens_t *tokens)
{
    lex_tokens_t *expect = build_expect_tokens(test3_pragma_digit_expect_tokens);
    lex_tokens_t *e = expect,
                 *t = tokens;

    while(1)
    {
        if(t == NULL && e == NULL)
            break;

        if(t->token->pos != e->token->pos)
            return -1;
        if(t->token->len != e->token->len)
            return -2;
        if(t->token->line != e->token->line)
            return -3;
        if(strcmp(t->token->sym, e->token->sym) != 0)
            return -4;
        if(t->token->typ != e->token->typ)
            return -5;

        t = t->next;
        e = e->next;
    }
    return 0;
}

static lex_token_t test3_pragma_str_tokens[] = {
    {.typ = LEX_TOKEN_EOL},
    {}
};

static int lex_test3_pragma_str(lex_tokens_t *tokens)
{
    lex_tokens_t *expect = build_expect_tokens(test3_pragma_str_tokens);
    return -1;
}

