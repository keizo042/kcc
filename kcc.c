#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kcc.h"

#define ERROR -1
#define DONE 0
#define CONTINUE 1

static lex_token_t* lex_token_new(uint64_t pos,uint64_t len, uint64_t line, char *sym, uint64_t typ)
{
        lex_token_t *token = (lex_token_t*)malloc( sizeof(struct lex_token_s));
        token->pos  = pos;
        token->len  = len;
        token->line = line;
        token->sym  = sym;
        token->typ = typ;
        return token;
}

static int lex_emit(lex_state *state, uint64_t typ)
{
    lex_tokens_t *toks = (lex_tokens_t*)malloc( sizeof(lex_tokens_t) );

    lex_token_t *old = state->data->token;
    old->typ =typ;
    old->sym  = (char *)malloc( sizeof(char) * ( old->len + 1));
    strncpy(old->sym, state->src + old->pos, old->len);
    toks->token = lex_token_new(old->pos + old->len, 0, old->line, NULL , typ);

    state->data->next = toks;
    state->data = toks;

    state->data->token->pos++;

    if( typ == LEX_TOKEN_EOL)
    {
        return DONE;
    }else
    {
        return  CONTINUE;
    }
}

static int lex_skip_commnet(lex_state *state)
{
    lex_token_t *token = state->data->token;
    while(1)
    {
        switch(state->src[token->pos])
        {
            case '\n':
                return CONTINUE;
            case '*':
                token->pos++;
                switch(state->src[token->pos])
                {
                    case '/':
                        token->pos++;
                        return CONTINUE;
                    default:
                        token->pos++;
                }
            default:
                continue;
        }
    }
}

static int lex_skip_until(lex_state *state, char c)
{
    lex_token_t *token = state->data->token;
    while(1)
    {
        if(state->src[token->pos] == c)
        {
            return CONTINUE;
        }
        token->pos++;
    }
}


static int lex_pragma(lex_state *state)
{

    return CONTINUE;
}

static int lex_identify(lex_state *state)
{
    char *src = state->src;
    lex_token_t *token = state->data->token;
    while(1)
    {
        switch(src[token->pos])
        {
            case ' ':
            case '\t':
                token->pos++;
                continue;
            case '\n':
            case '/':
                switch(src[token->pos])
                {
                    case '*':
                        return lex_skip_commnet(state);
                    case '/':
                        return lex_skip_until(state, '\n');
                    default:
                        goto fail;

                }
            case '#':
                token->pos++;
                return lex_pragma(state);

        }
    }

    return DONE;

fail:
    return  ERROR;
}

lex_state *lex(char *src)
{
    int c;
    lex_state *state = (lex_state*)malloc( sizeof(lex_state) );
    state->head = NULL;
    state->tail = NULL;
    state->data = (lex_tokens_t*)malloc( sizeof(lex_tokens_t));
    state->data->token = lex_token_new(0, 0, 0, NULL, LEX_TOKEN_UNDEFINED);
    state->src = src;
    while(0)
    {
        c = lex_identify(state);
        if(c != DONE)
        {
            break;
        }
    }

    return state;
}


parser_state *parse(lex_state *lex)
{
    parser_state *parser = NULL;
    return parser;
}

void compile()
{
}
