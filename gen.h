#ifndef GEN_H
#define GEN_H
#include "parser.h"
struct gen_info_t;
typedef struct gen_info_t gen_info_t;
gen_info_t* gen_info_init(parser_state*);
int gen_info_run();
int gen_info_error();
#endif
