#ifndef __KCC_LEX_H
#define __KCC_LEX_H

#define LEX_TOKEN_END 0 // ;
#define LEX_TOKEN_DIGIT 1
#define LEX_TOKEN_STRING 2
#define LEX_TOKEN_BRACE_L 3   // {
#define LEX_TOKEN_BRACE_R 4   //  }
#define LEX_TOKEN_BRACKET_L 5 // (
#define LEX_TOKEN_BRACKET_R 6 // )
#define LEX_TOKEN_CONNMA 7    // ,
#define LEX_TOKEN_CORON 8     // :
#define LEX_TOKEN_EQ 9        // =
#define LEX_TOKEN_LESS 10     // <
#define LEX_TOKEN_MORE 11     // >
#define LEX_TOKEN_IF 12
#define LEX_TOKEN_ELSE 13
#define LEX_TOKEN_WHILE 14
#define LEX_TOKEN_SWITCH 15
#define LEX_TOKEN_CASE 16
#define LEX_TOKEN_GOTO 17
#define LEX_TOKEN_KEYWORD 18 // struct, union, typedef etcetc...
#define LEX_TOKEN_IDENT 19
#define LEX_TOKEN_PLUS 20
#define LEX_TOKEN_MINUS 21
#define LEX_TOKEN_MULTI 22
#define LEX_TOKEN_DIV 23
#define LEX_TOKEN_SQUARE_BRACKET_L 24 // [
#define LEX_TOKEN_SQUARE_BRACKET_R 25 // ]
#define LEX_TOKEN_EOF 26
#define LEX_TOKEN_TYPE 27
#define LEX_TOKEN_QUESTION 28
#define LEX_TOKEN_EXCLAMATION 29
#define LEX_TOKEN_RETURN 30

#define LEX_FIN 0
#define LEX_CONTINUE 1
#define LEX_ERR 2

struct lex_state_s;
typedef struct lex_state_s lex_state;


int test100(char *src);
int test200(char *src);
int test300(char *src);
int test400(char *src);
#endif

