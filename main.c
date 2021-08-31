#include "resources.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("lc3 [image-file1] ...\n");
		exit(2);
	}

	for (int i = 1; 1 < argc; ++i)
	{
		if(!read_image(argv[i]))
		{
			printf("failed to load image: %s\n", argv[i]);
			exit(1);
		}
	}

	// load arguments
	int running = 1;

	enum { PC_START_LOCATION = 0x3000 };
	registers[R_PC] = PC_START_LOCATION;

	while(running)
	{
		uint16_t instruction = mem_read(registers[R_PC]++); //postfix decrements after returning value
		uint16_t op = instruction >> 12; // extract the op code from the instruction

		switch (op)
		{
			case OP_ADD:
				_add(instruction);
				break;

			
			case OP_AND:
				break;

			
			case OP_NOT:
				break;

			
			case OP_BR:
				break;
		
			case OP_JMP:
				break;

			case OP_JSR:
				break;

			case OP_LD:
				break;

			case OP_LDI:
				_ldi(instruction);
				break;

			case OP_LDR:
				break;

			case OP_LEA:
				break;

			case OP_ST:
				break;

			case OP_STI:
				break;

			case OP_STR:
				break;

			case OP_TRAP:
				break;

			case OP_RES:

			case OP_RTI:

			default: 	
				// BAD OP
				break;
		}
	}

	return 0;
}
