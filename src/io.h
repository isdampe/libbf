#ifndef BF_IO_H
#define BF_IO_H
#include "token.h"

static inline uint8_t is_bfchar(const uint8_t c);
struct bf_tokenset bf_tokenset_from_src_file(const char *fp);

#endif