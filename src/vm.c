#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "vm.h"

struct bf_vm_core bf_vm_init(struct bf_tokenset *instructions, size_t stack_size)
{
	struct bf_vm_core core = {
		.instructions = instructions,
		.stack_size = stack_size,
		.stack = calloc(stack_size, sizeof(uint8_t)),
		.sp = 0x0,
		.pc = 0x0
	};

	return core;

}

void bf_vm_destroy(struct bf_vm_core *vm)
{
	if (vm->stack != NULL)
		free(vm->stack);
}

void bf_vm_execute(struct bf_vm_core *core) {
	while (core->pc < core->instructions->length) {
		switch (core->instructions->tokens[core->pc].token) {
			case INC_DP:
				core->sp++;
			break;
			case DEC_DP:
				core->sp--;
			break;
			case INC_BYTE:
				core->stack[core->sp]++;
			break;
			case DEC_BYTE:
				core->stack[core->sp]--;
			break;
			case OUTPUT_BYTE:
				putchar(core->stack[core->sp]);
			break;
			case READ_BYTE:
				core->stack[core->sp] = getchar();
				char c;
				while ((c = getchar()) != '\n' && c != EOF) {;}
			break;
			case CND_OPEN:
				if (core->stack[core->sp] == 0) {
					while (++core->pc < core->instructions->length) {
						if (core->instructions->tokens[core->pc].token == CND_CLOSE)
							break;
					}

					if (++core->pc < core->instructions->length)
						continue;
					
					printf("FATAL: Unclosed condition token.");
					break;
					
				}
			break;
			case CND_CLOSE:
				if (core->stack[core->sp] != 0) {
					while (--core->pc >= 0) {
						if (core->instructions->tokens[core->pc].token == CND_OPEN)
							break;
					}

					if (core->pc++ > 0)
						continue;
					
					printf("FATAL: Unclosed condition token.");
					break;
					
				}
			break;
		}

		core->pc++;
	}
}