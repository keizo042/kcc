#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "gen.h"
#include "lex.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    int rc;

    lex_state *lexer = lex_state_init("1 + 1");
    rc               = lex_state_run(lexer);
    if (rc) {
        fprintf(stderr, "lex:%s\n", lex_state_error(lexer));
        return 1;
    }

    parser_state *parser = parser_state_init(lexer);
    rc                   = parser_state_run(parser);
    if (rc) {
        fprintf(stderr, "parse:%s\n", parser_state_error(parser));
        return 2;
    }

    gen_info_t *gen = gen_info_init(parser);
    rc              = gen_info_run(gen);
    if (rc) {
        return 3;
    }

    gen_info_print(gen);

    return 0;
}
