#include "test.h"


static int lex_test1(lex_tokens_t *l);

char *test1_code_function = "int func() {return 0; }";

static lex_token_t test1_expect_tokens[] = {
    { .pos = 0,     .len = 3,   .line = 0,  .sym = "int",       .typ = LEX_TOKEN_TYPE      },
    { .pos = 5,     .len = 4,   .line = 0,  .sym = "func",      .typ = LEX_TOKEN_ID        },
    { .pos = 10,    .len = 1,   .line = 0,  .sym = "(",         .typ = LEX_TOKEN_BRACKET_L },
    { .pos = 11,    .len = 1,   .line = 0,  .sym = ")",         .typ = LEX_TOKEN_BRACKET_R },
    { .pos = 13,    .len = 1,   .line = 0,  .sym = "{",         .typ = LEX_TOKEN_BRACE_L   },
    { .pos = 14,    .len = 6,   .line = 0,  .sym = "return",    .typ = LEX_TOKEN_RETURN    },
    { .pos = 21,    .len = 1,   .line = 0,  .sym = "0",         .typ = LEX_TOKEN_DIGIT     },
    { .pos = 22,    .len = 1,   .line = 0,  .sym = ";",         .typ = LEX_TOKEN_SEMICORON },
    { .pos = 24,    .len = 1,   .line = 0,  .sym = "}",         .typ = LEX_TOKEN_BRACE_R   },
    { .pos = 25,     .len = 0,   .line = 0,  .sym = "",          .typ = LEX_TOKEN_EOL       },
    {}
};

int lex_test1(lex_tokens_t *tokens)
{
    lex_tokens_t *expect = build_expect_tokens(test1_expect_tokens);

    lex_tokens_t *e = expect,
                 *t = tokens;
    while(1)
    {
        if(t == NULL && e == NULL)
        {
            break;
        }
        if(e->token->sym == NULL)
        {
            printf("not well-defined test data");
        }
        if(t->token->sym == NULL)
        {
            return -1;
        }
        if(strncmp(e->token->sym, t->token->sym, strlen(e->token->sym)) != 0)
        {
            return -1;
        }

        if(e->token->typ != t->token->typ)
        {
            return -2;
        }
        e = e->next;
        t = t->next;
    }

    expect_tokens_free(expect);
    return 0;

}

int main()
{
    int flag =0;
    lex_state *l;
        
    printf("test1: start\n");
    l = lex(test1_code_function);
    if(l == NULL)
    {
        flag = 1;
        printf("test1: lex return null ptr\n");
        goto test1_end;
    }else
    {
        printf("test1:lex pass...\n");
    }

    if(lex_test1(l->head))
    {
        flag = 1;
        printf("lex_test1 fail\n");
        goto test1_end;
    }else
    {
        printf("test1:\n");
    }
test1_end:

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
