#ifndef __KCC_LEXL_H
#define __KCC_LEXL_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

struct kcc_lex_context_s {
  size_t pos;
  size_t len;
};

typedef struct kcc_lex_context_s kcc_lex_context;

struct kcc_token_s{
};

typedef struct kcc_token_s kcc_token_t;
struct kcc_token_list_s {
  kcc_token_t *token;
  struct kcc_token_list_s *next;
};

typedef struct kcc_token_list_s kcc_token_list_t;
kcc_lex_context *kcc_lex_context_new();
kcc_token_list_t *kcc_lex(kcc_lex_context *);
#endif
