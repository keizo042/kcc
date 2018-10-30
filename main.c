#include "kcc.h"
#include<stdio.h>

int
main(int argc, char* argv[]) {
    kcc_lex_context *lexer = NULL;
    kcc_parser_context *parser = NULL;
    kcc_ast_t *ast = NULL;
    kcc_token_list_t *tokens = NULL;
    const char * code = argv[1];
    lexer = kcc_lex_context_new();
    if(!lexer){
        return -1;
    }
    tokens = kcc_lex(lexer);
    if(!tokens){
        return -1;
    }
    parser = kcc_parser_context_new(tokens);
    if(!parser){
        return -1;
    }
    ast = kcc_parse(parser);
    if(!ast){
        return -1;
    }
    if(!kcc_ast_print(ast)){
        puts("warn");
    }
}
