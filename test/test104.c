#include <stdio.h>
#include "lex.h"
#include "test.h"


int
main(int argc, char* argv[]) {
    char *test1 = "/* */";
    char *test2 = "//     ";
    char *test3 = "/*    ";
    char *test4 = "//  /* */";
    char *test5 = "/*  //  */";
    
    test(test400(test1) == LEX_FIN, __FILE__, "comment1");
    test(test400(test2) == LEX_FIN, __FILE__, "comment2");
    test(test400(test3) == LEX_ERR, __FILE__, "comment3");
    test(test400(test4) == LEX_FIN, __FILE__, "comment4");
    test(test400(test5) == LEX_FIN, __FILE__, "comment5");
    
    return 0;
}
