#ifndef BF_PRINT_H
#define BF_PRINT_H
#include "token.h"

#define bf_print_token(a) printf("0x%1x %c", a.token, a.dsasm)
void bf_print_tokenset(const struct bf_tokenset *set);

#endif