#ifndef ARCH_AMD_H
#define ARCH_AMD_H
#include "gen.h"

int arch_amd64_compile(gen_info_t *info);

const char *arch_amd64_error(gen_info_t *info);
#endif
