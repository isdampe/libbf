#ifndef BF_VM_H
#define BF_VM_H
#include <stdint.h>
#include <stddef.h>
#include "token.h"

struct bf_vm_core {
	struct bf_tokenset *instructions;
	uint8_t *stack;
	size_t stack_size;
	long sp;
	long pc;
};

struct bf_vm_core bf_vm_init(struct bf_tokenset *instructions, size_t stack_size);
void bf_vm_destroy(struct bf_vm_core *vm);
void bf_vm_execute(struct bf_vm_core *core);

#endif