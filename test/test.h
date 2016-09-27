#ifndef __KCC_TEST_H
#define __KCC_TEST_H
#include "kcc.h"
#include "lex.h"
#include "parser.h"
#include "ast.h"
#include "gen.h"

extern int test100(char *);

int test(int b, char *file, char *msg)
{
        if(b){
        }else{
                printf("%s     \t%s:fail\n", file, msg);
        }
        return b;
}
#endif
