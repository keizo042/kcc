#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "ast.h"

kcc_lex_context *kcc_lex_context_new(char *){
    kcc_lex_context *ctx = NULL;
    ctx = (kcc_lex_context *)malloc(sizeof(kcc_lex_context));
    return ctx;
}
