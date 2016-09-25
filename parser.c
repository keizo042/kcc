#include "parser.h"
#include "ast.h"
#include "lex.h"
#include <stdlib.h>
#include <string.h>



typedef int (*parser_f)(parser_state *);

struct parser_state {
    char *sym;
    parser_f func;
};



parser_state *parse(lex_state *lexer) {
    parser_state *parser = NULL;
    return parser;
}
