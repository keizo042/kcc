#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "parser.h"

lex_token_t testdata1[] = {
    {
        "2", LEX_TOKEN_DIGIT,
    },
    {
        "+", LEX_TOKEN_PLUS,
    },
    {
        "1", LEX_TOKEN_DIGIT,
    },
    {
        "", LEX_TOKEN_EOF,
    },
    {},
};

/*
static lex_token_list_t *construct(int n) {
    lex_token_list_t *list = NULL, *t = NULL, *holder = NULL;
    if (!data) {
        return NULL;
    }
    list        = malloc(sizeof(lex_token_list_t));
    list->token = data[0];
    holder      = list;
    for (int i = 1; data[i] != NULL; i++) {
        t            = malloc(sizeof(lex_token_list_t));
        t->token     = data[i];
        holder->next = t;
        holder       = t;
        if (data[i]->typ == LEX_TOKEN_EOF) {
            break;
        }
    }

    return list;
}
*/

int main(int argc, char *argv[]) {
    printf("not yet implemented\n");
    lex_state lexer = {};

    parser_state *parser = parser_state_init(&lexer);
    return 1;
}
