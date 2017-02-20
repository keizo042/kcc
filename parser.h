#ifndef PARSER_H
#define PARSER_H

#include "lex.h"
struct parser_state;
typedef struct parser_state parser_state;

parser_state *parser_state_new(lex_state*);
int parser_state_run(parser_state*);
int parser_state_error(parser_state*);
#endif
