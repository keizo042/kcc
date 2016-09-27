#ifndef __KCC_TEST_H
#define __KCC_TEST_H
#include "kcc.h"
#include "lex.h"
#include "parser.h"
#include "ast.h"
#include "gen.h"


void test(int b, char *file, char *msg)
{
        if(b){
        }else{
                printf("%s,%s:fail\n", file, msg);
        }
}
#endif
