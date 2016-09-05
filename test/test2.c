#include "test.h"

char *test2_code_comment = "// yuyushiki is awesome. //";
char *test2_code_comments =  "/* Domo Geek=san.\nNinja Slayer desu\n*/";
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
        if(e->token->typ != t->token->typ)
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

int main()
{
    lex_state *l2comment    =   NULL,
              *l2comments   =   NULL;
    int flag = 0;
    printf("test2:start\n");

    l2comment = lex(test2_code_comment);
    if(l2comment == NULL)
    {
        flag = 1;
        printf("test2: lex return null ptr\n");
        goto test2_end;
    }else
    {
        printf("test2:lex pass..\n");
    }

    if(lex_test2_comment(l2comment->head))
    {
        flag = 1;
        printf("test2: lex_test2 fail\n");
        goto test2_end;
    }else
    {
        printf("test2:\n");
    }
    l2comments = lex(test2_code_comments);
    if(l2comments == NULL)
    {
        printf("test2 comments null ptr\n");
        goto test2_end;
    }

    if(lex_test2_comments(l2comments->head) != 0)
    {
        printf("test2: fail"); 
        goto test2_end;
    }
            
test2_end:

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
