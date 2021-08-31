#include <stdlib.h>



/* Main memory */
uint16_t main_mem[UINT16_MAX];
		


/* Registers */
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



/* Operation codes (a comprehensive list of fundamental instructions) */
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



/* Condition flags (used for logical evaluations) */
enum
{
	FL_POS = 1 << 0, // positive 
	FL_ZRO = 1 << 1, // zero
	FL_NEG = 1 << 2  // negative
};



/* Helper functions */
uint16_t sign_extend(uint16_t x, int bit_count);
void update_flags(uint16_t reg);



/* LC3 operations */
void _add(uint16_t instr);
void _ldi(uint16_t instr);
void _and(uint16_t instr)
