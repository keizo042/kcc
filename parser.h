#ifndef __KCC_PARSER_H
#define __KCC_PARSER_H
#include "ast.h"
#include "lex.h"
#include "parser.h"

struct kcc_parser_context_s {
};

typedef struct kcc_parser_context_s kcc_parser_context;
kcc_parser_context *kcc_parser_context_new();
#endif

