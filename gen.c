#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "parser.h"
#include "gen.h"

gen_info_t *gen_info_init(parser_state *state){
    gen_info_t *info = (gen_info_t*)malloc( sizeof(gen_info_t) );
    return info;
}

int gen_info_run(gen_info_t* info){
    return 1;
}

const char* gen_info_error(gen_info_t *info){
    return "";
}

int gen_info_print(gen_info_t *info){
    return 1;
}
