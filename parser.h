#ifndef PARSER_H
#define PARSER_H

#include "lex.h"

struct parser_state;
typedef struct parser_state parser_state;

// structure for external api
typedef struct parser_state {
        lex_token_list_t *stream;
        lex_token_list_t *start;

        int err;
        char* errmsg;
} parser_state;

parser_state *parser_state_init(lex_state *);

int parser_state_run(parser_state *);
const char *parser_state_error(parser_state *);
int parser_state_print(parser_state *);
#endif
