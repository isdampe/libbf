#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "print.h"

void bf_print_tokenset(const struct bf_tokenset *set)
{
	for (size_t n=0; n<set->length; ++n) {
		printf("0x%04lx\t", n);
		bf_print_token(set->tokens[n]);
		printf("\n");
	}
}