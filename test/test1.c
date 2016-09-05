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
            ERROR("test1","test1", "expect token error");
        }
        if(t->token->sym == NULL)
        {
            ERROR("test1","test1", "token error");
            return -1;
        }
        if(strncmp(e->token->sym, t->token->sym, strlen(e->token->sym)) != 0)
        {
            ERROR("test1","test1", "mismatch token");
            return -1;
        }

        if(e->token->typ != t->token->typ)
        {
            ERROR("test1","test1", "mismatch type");
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
        
    l = lex(test1_code_function);
    if(l == NULL)
    {
        flag = 1;
        ERROR("test1","ptr check", "null");
        goto test1_end;
    }else

    if(lex_test1(l->head))
    {
        flag = 1;
        ERROR("test1","lex_test1", "fail");
        goto test1_end;
    }else
test1_end:

    if(flag == 0)
    {
    return 0;
    }else
    {
    return -1;
    }
}
