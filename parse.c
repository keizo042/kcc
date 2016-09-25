#include "lex.h"
#include "parse.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>


struct parser_state {
    char *sym;
};

typedef struct parser_state parser_state;



parser_state *parse(lex_state *lexer) {
    parser_state *parser;
    return parser;
}
