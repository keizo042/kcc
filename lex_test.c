#include "lex.h"

static int testing(char *code) {
    lex_state *lexer = lex_state_init(code);
    int rc           = lex_state_run(lexer);
    if (rc) {
        fprintf(stderr, "lex:%s\n", lex_state_error(lexer));
        return 1;
    }
}


int test1() { return testing("1 + 2"); }

int test2() { return testing("1+2"); }

int test3() { return testing("\"\""); }

int test4() { return testing("\"hello world\""); }

int test5() { return testing(""); }

typedef int (*testfn_t)();

testfn_t testcase[] = {test1, test2, test3, test4, test5, NULL};

int main() {
    for (int i = 0; testcase[i] != NULL; i++) {
        testfn_t testfn = testcase[i];
        if (testfn()) {
            return 1;
        }
    }
    return 0;
}
