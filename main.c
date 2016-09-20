#include "kcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *text[] = {"usage : kcc [file] ", " ", " ", " ", " ", NULL};

void usage() {
  for (int i = 0; i < 7; i++) {
    puts(text[i]);
  }
}

void optparse() {}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    usage();
    return 0;
  }

  return 0;
}
