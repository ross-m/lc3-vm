#include <stdlib.h>

// Main memory
uint16_t main_mem[UINT16_MAX];

// Registers
enum 
{
	R_R0 = 0,
	R_R1,
	R_R2,
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,
	R_PC,
	R_COND,
	R_COUNT
};

uint16_t registers[R_COUNT];

// Operation codes (a comprehensive list of fundamental instructions)

enum 
{
	OP_BR = 0, // branch
	OP_ADD,    // add
	OP_LD, 	   // load
	OP_ST, 	   // store
	OP_JSR,	   // jump register
	OP_AND,    // bitwise AND
	OP_LDR,	   // load register
	OP_STR,    // store register
	OP_RTI,    // unused
	OP_NOT,    // bitwise NOT
	OP_LDI,    // load indirect
	OP_STI,    // store indirect
	OP_JMP,    // jump
	OP_RES,    // reserved (unused)
	OP_LEA,    // load effective address
	OP_TRAP    // execute trap
};

// Condition flags (used for logical evaluations)

enum
{
	FL_POS = 1 << 0, // positive 
	FL_ZRO = 1 << 1, // zero
	FL_NEG = 1 << 2  // negative
};

int main(int argc, char *argv[])
{
	// load arguments
	int running = 1;

	enum { PC_START_LOCATION = 0x3000 };
	registers[R_PC] = PC_START;	

	while(running)
	{
		uint16_t instruction = mem_read(registers[R_PC]++); //postfix decrements after returning value
		uint16_t op = instruction >> 12; // extract the op code from the instruction

		switch (op)
		{
			case OP_ADD:
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
