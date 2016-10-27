#ifndef __KCC_PARSER_H
#define __KCC_PARSER_H
#include "lex.h"
struct parser_state;
typedef struct parser_state parser_state;
parser_state *parse(lex_state *);
#endif
