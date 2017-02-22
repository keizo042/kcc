#include <stdlib.h>
#include "parser.h"

parser_state *parser_state_init(lex_state *lexer){
    parser_state *state = (parser_state*)malloc( sizeof(parser_state));
    return state;
}

int parser_state_run(parser_state *state){
    return 1;
}
const char* parser_state_error(parser_state *parser){
    return "";
}
