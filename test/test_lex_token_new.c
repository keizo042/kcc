#include "test.h"
#include "kcc.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  lex_token_t *token = NULL;
  if (test_lex_token_new() == ERR) {
    ERROR("lex_token_new", "init", "fail");
  }
  return 0;
}
