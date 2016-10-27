#ifndef __KCC_GEN_H
#define __KCC_GEN_H
#include "parser.h"
struct gen_info_s;
typedef struct gen_info_s gen_info_t;
gen_info_t *gen(parser_state *);
#endif
