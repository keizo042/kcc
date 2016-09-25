#include "lex.h"
#include "parser.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>


struct parser_state;
typedef struct parser_state parser_state;

typedef int (*parser_f)(parser_state *);

struct parser_state {
    char *sym;
    parser_f func;

};



parser_state *parse(lex_state *lexer) {
    parser_state *parser = NULL;
    return parser;
}
