#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "io.h"
#include "token.h"

static inline uint8_t is_bfchar(const uint8_t c)
{
	char bfschars[] = "><+-.,[]";
	for (int i=0; i<8; ++i)
		if (c == bfschars[i])
			return 1;

	return 0;
}

struct bf_tokenset bf_tokenset_from_src_file(const char *fp)
{
	FILE *fh = fopen(fp, "r");
	assert(fh != NULL);

	fseek(fh, 0, SEEK_END);
	long size = ftell(fh);
	fseek(fh, 0, SEEK_SET);
	assert(size > 0);

	uint8_t *src = malloc(size * sizeof(uint8_t));
	long n = 0;

	char c;
	while ((c = fgetc(fh)) != EOF)
		if (is_bfchar(c) > 0)
			src[n++] = c;

	fclose(fh);

	if (n > 0 && n != size)
		src = realloc(src, n);

	return bf_tokenize(src, n);

}