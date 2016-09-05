#include "test.h"

char *test3_code_pragma_digit = "#define PRAGMA 1";
char *test3_code_pragma_str = "#define STR \"string\" ";


static int lex_test3_pragma_digit(lex_tokens_t *l);
static int lex_test3_pragma_str(lex_tokens_t *tokens);

int main()
{
    int flag = 0;
    lex_state *l3digit,
              *l3str;

    printf("test3:start\n");
    l3digit = lex(test3_code_pragma_digit);
    if(l3digit == NULL)
    {
        flag = 1;
        printf("test3: null ptr\n");
        goto test3_end;

    }else
    {
        printf("test3:\n");
    }
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

