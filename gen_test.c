#include "ast.h"
#include "gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int testing(parser_state *s) {
    gen_info_t *gen = gen_info_init(s);
    if (gen_info_run(gen)) {
        return 1;
    }
    return 0;
}

int test1() { return 1; }

typedef int (*testfn_t)();

testfn_t testcase[] = {test1, NULL};

int main() {
    for (int i = 0; testcase[i] != NULL; i++) {
        testfn_t testfn = testcase[i];
        if(testfn()){
            return 1;
        }
    }
    return 1;
}
