#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kcc.h"


static lex_token_t* lex_token_new(uint64_t pos,uint64_t len, uint64_t line, char *sym, uint64_t typ)
{
        lex_token_t *token = (lex_token_t*)malloc( sizeof(lex_token_t) );
        token->pos  = pos;
        token->len  = len;
        token->line = line;
        token->sym  = sym;
        token->typ  = typ;
        return token;
}

static lex_state* lex_state_open(char *src)
{
    lex_state *state = (lex_state*)malloc( sizeof(lex_state) );
    state->head = NULL;
    state->tail = NULL;
    state->data = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
    state->data->next = NULL;
    state->data->token = lex_token_new(0, 0, 0, NULL, LEX_TOKEN_UNDEFINED);
    state->src = src;
    return state;
}

static int lex_emit(lex_state *state, uint64_t typ)
{
    lex_token_t *old = state->data->token;
    lex_tokens_t *new_tokens = (lex_tokens_t*)malloc( sizeof( lex_tokens_t) );
    old->sym  = (char *)malloc( sizeof(char) * ( old->len + 1));
    if(old->len != 0)
    {
        strncpy(old->sym, state->src + old->pos, old->len);
    }else
    {
        old->sym[0] = '\0';
    }

    new_tokens->token = lex_token_new(old->pos + old->len, 0, old->line, NULL ,LEX_TOKEN_UNDEFINED );

    state->data->next = new_tokens;
    state->data = new_tokens;


    if( typ == LEX_TOKEN_EOL)
    {
        return DONE;
    }else
    {
        state->data->token->pos++;
        return  CONTINUE;
    }
}


static int lex_token(lex_state *state)
{

    lex_token_t *token = state->data->token;
    if( !ISASCII(state->src[token->pos]))
    {
        return ERR;
    }
    token->len++;

    while(1)
    {
        if( ISASCII(state->src[token->pos + token->len]) || ISDIGIT(state->src[token->len]) )      
        {
            token->len++;
        }{
            token->len--;
            lex_emit(state, LEX_TOKEN_TOKEN);
            break;
        }
    }

    return CONTINUE;
}

static int lex_string(lex_state *state)
{
    lex_token_t *token = state->data->token;
    if( state->src[token->pos] != '"')
    {
        return ERR;
    }
    token->pos++;
    while(1)
    {
        if(state->src[token->pos + token->len] == '"')
        {
            if(token->len > 0)
            {
            token->len--;
            }
            lex_emit(state, LEX_TOKEN_STR);
            return CONTINUE;

        }
        token->len++;
    }

    return CONTINUE;
}

static int lex_digit(lex_state *state)
{
    lex_token_t *token = state->data->token;
    while(1)
    {
        if( ISDIGIT(state->src[token->pos + token->len]) )
        {
            token->len++;
            continue;
        }

        if(state->src[token->pos + token->len] == ' ')
        {
            token->len--;
            goto accept;
        }else
        {
            break;
        }
        goto fail;

    }

    if(state->src[token->pos + token->len] == '.')
    {
        token->len++;
        while(1)
        {
            if(ISDIGIT(state->src[token->pos + token->len]) )
            {
                token->len++;
                continue;
            }
            if(state->src[token->pos + token->len] == ' ')
            {
                token->len--;
                goto accept;
            }else
            {
                break;
            }
            goto fail;
        }
    }

    if(state->src[token->pos + token->len] == 'e')
    {
        token->len++;
        while(1)
        {
            if( !ISDIGIT(state->src[token->pos + token->len]) )
            {
                break;
            }
            token->len++;
        }
    }
    if(state->src[token->pos +  token->len] == ' ' || state->src[token->pos + token->len] == '\0' || state->src[token->pos + token->len] == '\t' || state->src[token->pos + token->len] == '\n')
    {
        token->len--;
        goto accept;
    }


fail:
    return ERR;

accept:
    lex_emit(state, LEX_TOKEN_DIGIT);
    return CONTINUE;
}

static int lex_skip_commnet(lex_state *state)
{
    lex_token_t *token = state->data->token;
    if(state->src[token->pos] != '/')
    {
        return ERR;
    }
    if(state->src[token->pos + 1] != '*')
    {
        return ERR;
    }
    token->pos += 2;
    while(1)
    {

        switch(state->src[token->pos])
        {
            case '\n':
                token->line++;
                token->pos++;
                continue;
            case '\0':
                return ERR;
            case '*':
                if(state->src[token->pos + 1] == '/')
                {
                    token->pos += 2;
                    return CONTINUE;
                }
            default:
                token->pos++;
        }
    }
    return ERR;
}

static int lex_skip_brank(lex_state *state)
{
    while(state->src[state->data->token->pos] == ' ')
    {
        state->data->token->pos++;
    }
    return CONTINUE;
}

static int lex_skip_until(lex_state *state, char c)
{
    lex_token_t *token = state->data->token;
    while(1)
    {
        if(state->src[token->pos] == '\0')
        {
            return ERR;
        }
                 
        if(state->src[token->pos] == c)
        {
            return CONTINUE;
        }
        token->pos++;
    }
}


static int lex_pragma(lex_state *state)
{
    int n = strncmp(state->src + state->data->token->pos, "define", strlen("define"));
    if(n == 0)
    {
    }
    
    n = strncmp(state->src + state->data->token->pos, "include", strlen("include"));
    if(n == 0)
    {
    }
    n = strncmp(state->src + state->data->token->pos, "pragma", strlen("pragma"));
    if(n == 0)
    {
    }

    n = strncmp(state->src + state->data->token->pos, "if", strlen("if"));
    if( n == 0)
    {
    }

    n = strncmp(state->src + state->data->token->pos, "ifndef", strlen("ifndef"));
    if( n == 0 )
    {
    }

    n = strncmp(state->src + state->data->token->pos, "endif", strlen("endif"));
    if( n == 0)
    {
    }
    return ERR;
}

static int lex_text(lex_state *state)
{
    char *src = state->src;
    lex_token_t *token = state->data->token;
    while(1)
    {
        switch(src[token->pos])
        {
            case '\0':
                lex_emit(state, LEX_TOKEN_EOL);
                return DONE;
            case ' ':
            case '\t':
                token->pos++;
                continue;
            case '\n':
                token->line++;
                token->pos++;
                continue;
            case '/':
                switch(src[token->pos + 1])
                {
                    case '*':
                        return lex_skip_commnet(state);
                    case '/':
                        return lex_skip_until(state, '\n');
                    default:
                        return ERR;

                }
            case '#':
                token->pos++;
                return lex_pragma(state);
            case '"':
                return lex_string(state);
            default:
                if(strncmp(src + token->pos, "int", strlen("int")) == 0)
                {
                    token->pos += strlen("int");
                    lex_emit(state, LEX_TOKEN_TYPE);
                    lex_skip_brank(state);
                    return lex_token(state);
                }


        }
    }

    return DONE;

}

lex_state *lex(char *src)
{
    int c = ERR;
    lex_state *state = lex_state_open(src);
    while(0)
    {
        c = lex_text(state);
        if(c != DONE)
        {
            break;
        }
    }

    if(c == ERR)
    {
        return NULL;
    }
    return state;
}


parser_state *parse(lex_state *lex)
{
    parser_state *parser = NULL;
    return parser;
}

void compile(const char *src)
{
}





/*

test utility 

*/


int test_lex_digit(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_digit(state);
}

int test_lex_string(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_string(state);
}

int test_lex_skip_comment(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_skip_commnet(state);
}

int test_lex_skip_until()
{
    char *test = "abcdefg hijklmn opqrs tuvw xyz ";
    lex_state *state = lex_state_open(test);

    if(lex_skip_until(state,'a') != CONTINUE)
    {
        return ERR;

    }

    if(lex_skip_until(state, ' ') != CONTINUE)
    {
        return ERR;
    }

    if(lex_skip_until(state, 'z') != CONTINUE)
    {
        return ERR;
    }

    return CONTINUE;
}

int test_lex_token_new(lex_token_t *token)
{
    return ERR;
}

