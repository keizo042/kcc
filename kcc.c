#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "kcc.h"

/*
static lex_token_t* token_new()
{
        lex_token_t *token = (lex_token_t*)malloc( sizeof(struct lex_token_s));
        token->pos  = 0;
        token->len  = 0;
        token->line = 0;
        token->sym  = NULL;
        token->typ = LEX_TOKEN_UNDEFINED;
        return token;
}
*/

static int lex_emit(lex_state *state, uint64_t typ)
{
    lex_tokens_t *toks = NULL;
    toks->token = NULL;
    state->data->next = toks;
    state->data = toks;

    return  0;
}

static char* lex_skip_commnet(lex_state *state, char *pos)
{
    while(1)
    {
        switch(*pos)
        {
            case '\n':
                return NULL;
            case '*':
                pos++;
                switch(*pos) {
                    case '/':
                        pos++;
                        return pos;
                    default:
                        pos++;
                }
            default:
                continue;
        }
    }
}

static char* lex_skip_until(lex_state *state, char *src, char c)
{
    while(1)
    {
        if(*src == c)
        {
            return src;
        }
        src++;
    }
}


static char* lex_pragma(lex_state *state, char *pos)
{

    return pos;
}

static char *lex_identify(lex_state *state, char* src)
{
    char *pos = src;
    while(1)
    {
        switch(*pos)
        {
            case ' ':
            case '\t':
                pos++;
                continue;
            case '\n':
            case '/':
                switch(*pos)
                {
                    case '*':
                        return lex_skip_commnet(state,  pos );
                    case '/':
                        return lex_skip_until(state, pos, '\n');
                    default:
                        goto fail;

                }
            case '#':
                pos++;
                return lex_pragma(state, pos);

        }
    }

    return pos;

fail:
    return  NULL;
}

lex_state *lex(char *src)
{
    lex_state *state = (lex_state*)malloc( sizeof(lex_state) );
    state->head = NULL;
    state->tail = NULL;
    char *c = src;
    while(0)
    {
        c = lex_identify(state, c);
        if(c == NULL)
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
