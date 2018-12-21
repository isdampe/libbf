#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "token.h"

static struct bf_token parse_byte(const uint8_t byte)
{
	struct bf_token result = {
		.token = NOP,
		.dsasm = byte
	};

	switch (byte) {
		case '>':
			result.token = INC_DP;
			break;
		case '<':
			result.token = DEC_DP;
			break;
		case '+':
			result.token = INC_BYTE;
			break;
		case '-':
			result.token = DEC_BYTE;
			break;
		case '.':
			result.token = OUTPUT_BYTE;
			break;
		case ',':
			result.token = READ_BYTE;
			break;
		case '[':
			result.token = CND_OPEN;
			break;
		case ']':
			result.token = CND_CLOSE;
			break;
	}

	assert(result.token != NOP);
	return result;
}

struct bf_tokenset bf_tokenize(const uint8_t *data, size_t length)
{
	struct bf_tokenset set;
	set.tokens = malloc(length * sizeof(struct bf_token));	
	set.length = 0;

	for (size_t i=0; i<length; ++i) {
		struct bf_token token = parse_byte(data[i]);
		if (token.token != NOP) {
			set.tokens[set.length].token = token.token;
			set.tokens[set.length++].dsasm = token.dsasm;
		}
	}

	if (set.length > 0 && set.length != length)
		set.tokens = realloc(set.tokens, set.length -1);

	return set;
}

void bf_tokenset_destroy(struct bf_tokenset *set)
{
	if (set->tokens != NULL)
		free(set->tokens);
}
