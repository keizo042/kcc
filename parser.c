#include "parser.h"
#include "ast.h"
#include "lex.h"
#include <stdlib.h>
#include <string.h>


int parse_start(parser_state *);

parser_state *parse(lex_state *lexer) {
    parser_state *parser = NULL;
    parser = malloc(sizeof(parser_state));
    parser->stream = lexer->head;
    parse_start(parser);
    return parser;
}

int parse_start(parser_state *state) {

    switch (state->stream->token->typ) {
    case LEX_TOKEN_END:
    case LEX_TOKEN_DIGIT:
    case LEX_TOKEN_STRING:
    case LEX_TOKEN_PLUS:
    case LEX_TOKEN_MINUS:
    case LEX_TOKEN_DIV:
    case LEX_TOKEN_MULTI:
    case LEX_TOKEN_EQ:
    case LEX_TOKEN_LESS:
    case LEX_TOKEN_MORE:
    case LEX_TOKEN_BRACE_L:
    case LEX_TOKEN_BRACE_R:
    case LEX_TOKEN_BRACKET_L:
    case LEX_TOKEN_BRACKET_R:
    case LEX_TOKEN_SQUARE_BRACKET_L:
    case LEX_TOKEN_SQUARE_BRACKET_R:
    case LEX_TOKEN_CONNMA:
    case LEX_TOKEN_CORON:
    case LEX_TOKEN_SWITCH:
    case LEX_TOKEN_CASE:
    case LEX_TOKEN_GOTO:
    case LEX_TOKEN_IF:
    case LEX_TOKEN_WHILE:
    case LEX_TOKEN_ELSE:
    case LEX_TOKEN_IDENT:
    case LEX_TOKEN_TYPE:
    case LEX_TOKEN_RETURN:
    case LEX_TOKEN_KEYWORD:
    case LEX_TOKEN_EXCLAMATION:
    case LEX_TOKEN_QUESTION:
    case LEX_TOKEN_EOF:
    default:
        exit(-1);
    }
    return 0;
}

int parse_binop(parser_state *state)
{
    return 0;
}
