#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kcc.h"

#define lex_cmp(state,x) (strncmp(state->src + state->data->token->pos, (x), strlen((x))) == 0)


static int lex_emit(lex_state *, uint64_t);
static int lex_digit(lex_state *);
static int lex_string(lex_state *);
static int lex_skip_brank(lex_state *);
static int lex_skip_until(lex_state *, char);
static int lex_skip_comment(lex_state *);
static int lex_ident(lex_state *);
static int lex_text(lex_state *);


static keyword_t keywords[] = {
        { .sym = "if", .typ = LEX_TOKEN_IF},
        { .sym = "while", .typ = LEX_TOKEN_WHILE },
        { .sym = "sizeof", .typ = LEX_TOKEN_SIZEOF },
        { .sym = "return", .typ = LEX_TOKEN_RETURN },
        { .sym = "goto", .typ = LEX_TOKEN_GOTO},
        { .sym = "switch", .typ = LEX_TOKEN_SWITCH},
        { .sym = "continue", .typ = LEX_TOKEN_CONTINUE},
        { .sym = "else", .typ = LEX_TOKEN_ELSE},
        { .sym = "for", .typ = LEX_TOKEN_FOR},
        { .sym = "typefef", .typ = LEX_TOKEN_TYPEDEF},
        { .sym = "struct", .typ = LEX_TOKEN_STRUCT},
        {}
};

static  char *typs[] = {
        "int",
        "char",
        "long",
        "short",
        "float",
        "void",
        "double",
        NULL
};


static specifier_t specifiers[] = {
        {"signed", LEX_TOKEN_SIGNED},
        {"unsigned", LEX_TOKEN_UNDEFINED},
        {"volatile", LEX_TOKEN_VOLATILE },
        {"extern", LEX_TOKEN_EXTERN },
        {"static", LEX_TOKEN_STATIC },
        {"register", LEX_TOKEN_REGISTER },
        {"union", LEX_TOKEN_UNION },
        {}

};

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

    new_tokens->token = lex_token_new(old->pos + old->len, 0, old->line, NULL , LEX_TOKEN_UNDEFINED);

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




static int lex_ident(lex_state *state)
{
    lex_token_t *token = state->data->token;
    int i = 0;
head:
    while(1)
    {
        for(i =0; keywords[i].sym != NULL; i++)
        {
            
        }
        for(i = 0; specifiers[i].sym != NULL; i++)
        {
        }
        for(i =0; typs[i] != NULL; i++)
        {
        }

    }


type:
    if(state->src[token->pos + token->len + 1] == ' ')
    {
        return  lex_emit(state, LEX_TOKEN_TYPE);
    }
    if(ISASCII(state->src[token->pos + token->len + 1]))
    {
        goto head;
    }

fail:
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
            case ';':
                token->len++;
                return lex_emit(state, LEX_TOKEN_END);
            case '(':
                token->len++;
                return lex_emit(state, LEX_TOKEN_BRACE_L);
            case ')':
                token->len++;
                return lex_emit(state, LEX_TOKEN_BRACE_R);
            case '{':
                token->len++;
                return lex_emit(state, LEX_TOKEN_BRACKET_L);
            case '}':
                token->len++;
                return lex_emit(state, LEX_TOKEN_BRACKET_R);
            case '=':
                token->len++;
                return lex_emit(state, LEX_TOKEN_EQ);
            case '+':
                token->len++;
                return  lex_emit(state, LEX_TOKEN_PLUS);
            case '-':
                token->len++;
                return lex_emit(state, LEX_TOKEN_MINUS);
            case '*':
                token->len++;
                return lex_emit(state, LEX_TOKEN_ASTARISK);

            case '/':
                switch(src[token->pos + 1])
                {
                    case '*':
                        return lex_skip_commnet(state);
                    case '/':
                        return lex_skip_until(state, '\n');
                    default:
                        token->len++;
                        return lex_emit(state, LEX_TOKEN_DIV);

                }
            case '#':
                token->pos++;
                return lex_pragma(state);
            case '"':
                return lex_string(state);
            default:
                return lex_ident(state);

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
        switch(c = lex_text(state))
        {
            case ERR:
                break;
            case DONE:
                break;
            case CONTINUE:
                continue;

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


int test_lex_token(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_token(state);
}

int test_lex_skip_comment(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_skip_commnet(state);
}

int test_lex_skip_until(char *src, char c)
{

    lex_state *state = lex_state_open(src);
    return  lex_skip_until(state,c);
}

int test_lex_skip_brank(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_skip_brank(state);
}

int test_lex_token_new(lex_token_t *token)
{
     token = lex_token_new(0, 0, 0, "", LEX_TOKEN_UNDEFINED);
     return CONTINUE;
}


int test_lex_token_ident(char *src)
{
    lex_state *state = lex_state_open(src);
    return lex_ident(state);
}
