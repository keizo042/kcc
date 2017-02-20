#ifndef LEX_H
#define LEX_H

struct lex_state;
typedef struct lex_state lex_state;
lex_state lex_init();
int lex_state_set_src(lex_state, char*);
int lex_state_run();
int lex_state_error(lex_state*state);
#endif // LEX_H
