#ifndef BF_TOKENIZE_H
#define BF_TOKENIZE_H
#include <stdint.h>
#include <stddef.h>

enum bf_token_type {
	INC_DP,
	DEC_DP,
	INC_BYTE,
	DEC_BYTE,
	OUTPUT_BYTE,
	READ_BYTE,
	CND_OPEN,
	CND_CLOSE,
	NOP
};

struct bf_token {
	enum bf_token_type token;
	uint8_t dsasm;
};

struct bf_tokenset {
	struct bf_token *tokens;
	size_t length;
};

static struct bf_token parse_byte(const uint8_t byte);
struct bf_tokenset bf_tokenize(const uint8_t *data, size_t length);
void bf_tokenset_destroy(struct bf_tokenset *set);

#endif
