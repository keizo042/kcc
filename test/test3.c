#include "test.h"

char *test3_code_pragma_digit = "#define PRAGMA 1";
char *test3_code_pragma_str = "#define STR \"string\" ";

static int lex_test3_pragma_digit(lex_tokens_t *l);
static int lex_test3_pragma_str(lex_tokens_t *tokens);

int main() {
  int flag = 0;
  lex_state *l3digit, *l3str;

  l3digit = lex(test3_code_pragma_digit);
  if (l3digit == NULL) {
    flag = 1;
    ERROR("test3", "test3_code_pragma_digit", "fail to lex");
    goto test3_end;
  }
  if (lex_test3_pragma_digit(l3digit->head) != 0) {
    flag = 1;
    goto test3_end;
  }
  l3str = lex(test3_code_pragma_str);
  if (lex_test3_pragma_str(l3str->head) != 0) {
    ERROR("test3", "lex_test3_pragma_str", "fail");
    flag = 1;
    goto test3_end;
  }
test3_end:

  if (flag == 0) {
    return 0;
  } else {
    return -1;
  }
}

static lex_token_t test3_pragma_digit_expect_tokens[] = {{.typ = LEX_TOKEN_EOL},
                                                         {}};

static int lex_test3_pragma_digit(lex_tokens_t *tokens) {
  lex_tokens_t *expect = build_expect_tokens(test3_pragma_digit_expect_tokens);
  lex_tokens_t *e = expect, *t = tokens;

  while (1) {
    if (t == NULL && e == NULL) {
      break;
    }

    if (strcmp(t->token->sym, e->token->sym) != 0) {
      ERROR("test3", "lex_test3_pragma_digit", "mismatch sym");
      return -4;
    }
    if (t->token->typ != e->token->typ) {
      ERROR("test3", "lex_test3_pragma_digit", "mismatch type");
      return -5;
    }

    t = t->next;
    e = e->next;
  }
  return 0;
}

static lex_token_t test3_pragma_str_tokens[] = {{.typ = LEX_TOKEN_EOL}, {}};

static int lex_test3_pragma_str(lex_tokens_t *tokens) {
  lex_tokens_t *expect = build_expect_tokens(test3_pragma_str_tokens);
  lex_tokens_t *e = expect, *t = tokens;

  while (1) {
    if (e == NULL && t == NULL) {
      break;
    }
    if (strcmp(e->token->sym, t->token->sym) != 0) {
      ERROR("test3", "lex_test3_pragma_str", "mismatch symbol");
      return -1;
    }
    if (e->token->typ != t->token->typ) {
      ERROR("test3", "lex_test3_pragma_str", "mismatch type");
      return -2;
    }
  }
  return 0;
}
