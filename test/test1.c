#include "test.h"

char *test1_code_function = "int func() {return 0; }";
static int lex_test1(lex_tokens_t *l);

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
