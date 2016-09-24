#include "test.h"
#include "kcc.h"
#include <stdio.h>

#define F "test_lex_skip_until"
int main(int argc, char *argv[]) {

  char *test = "abcdefg hijklmn opqrs tuvw xyz ";
  char *comment = "//hello world\n";

  TEST(test_lex_skip_until(test, 'a') != CONTINUE, F, "test1", "fail");
  TEST(test_lex_skip_until(test, ' ') != CONTINUE, F, "test2", "fail");
  TEST(test_lex_skip_until(test, 'z') != CONTINUE, F, "test3", "fail")
  TEST(test_lex_skip_until(comment, '\n') != CONTINUE, F, "test3", "fail")
  TEST(test_lex_skip_until(test, '1') != ERR, F, "test3", "fail")
}
