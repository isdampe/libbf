#include <stdio.h>
#include <stdint.h>
#include "token.h"
#include "vm.h"
#include "io.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: bf [source.bf]\n");
		return 1;
	}

	struct bf_tokenset tokens = bf_tokenset_from_src_file(argv[1]);
	struct bf_vm_core core = bf_vm_init(&tokens, 30000);

	bf_vm_execute(&core);

	bf_tokenset_destroy(&tokens);
	bf_vm_destroy(&core);

	return 0;
}
