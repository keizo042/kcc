#include "gen.h"
#include "lex.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int debug(int argc, char **argv);
int help(int o);

int main(int argc, char *argv[]) {
    lex_state *lexer      = NULL;
    parser_state *parser  = NULL;
    gen_info_t *generater = NULL;
    if (argc < 2) {
        puts("less arguments");
        return -1;
    }
    if (strncmp("debug", argv[1], strlen("debug")) == 0) {
        debug(argc - 1, argv + 1);
        return 0;
    }

    lexer = lex(argv[1]);
    if (lexer == NULL) {
        printf("kcc lex: fail\n");
        return -1;
    }
    parser = parse(lexer);
    if (parser == NULL) {
        printf("kcc parse: fail\n");
        return -1;
    }
    generater = gen(parser);
    if (generater == NULL) {
        return -1;
    }
    return 0;
}

int debug(int argc, char **argv) {
    lex_state *lexer     = NULL;
    parser_state *parser = NULL;
    if (argc < 2) {
        printf("kcc debug: command needs something\n");
        return -1;
    }
    if (strncmp("lex", argv[1], strlen("lex")) == 0) {
        if (argc < 3) {
            printf("arguments need more than three arguments\n");
            return -1;
        }
        lexer = lex(argv[2]);
        if (lexer == NULL) {
            printf("error:lex\n");
            return -1;
        }
        lex_tok_stream_pp(lexer->head);
        return 0;
    }
    if (strncmp("parse", argv[1], strlen("parse")) == 0) {
        if (argc < 3) {
            return -1;
        }
        lexer  = lex(argv[2]);
        parser = parse(lexer);
        if (parser == NULL) {
            printf("kcc error:parse\n");
            return -1;
        }
        return 0;
    }
    printf("kcc: nothing to do\n");
    return 0;
}

int help(int o) { return 0; }
