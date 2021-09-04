#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <signal.h>


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
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};



/* trap routines */
enum
{
	TRAP_GETC = 0x20,  // get character (no echo) 
	TRAP_OUT = 0x21,   // output a character
	TRAP_PUTS = 0x22,  // output a word string
	TRAP_IN = 0x23,    // get character (echo)
	TRAP_PUTSP = 0x24, // output a byte string
	TRAP_HALT = 0x25   // halt program
};



/* memory mapped registers */
enum
{
	MR_KBSR = 0xFE00, // keyboard status
	MR_KBDR = 0xFE02 // keyboard data
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
void _br(uint16_t instr);
void _add(uint16_t instr);
void _ld(uint16_t instr);
void _st(uint16_t instr);
void _jsr(uint16_t instr);
void _and(uint16_t instr);
void _ldr(uint16_t instr);
void _str(uint16_t instr);
void _rti(uint16_t instr);
void _not(uint16_t instr);
void _ldi(uint16_t instr);
void _sti(uint16_t instr);
void _jmp(uint16_t instr);
void _res(uint16_t instr);
void _lea(uint16_t instr);



/* LC3 trap routines */
void _getc();
void _out();
void _puts();
void _in();
void _putsp();



/* miscellaneous helper functions */
void mem_write(uint16_t addr, uint16_t val);
uint16_t mem_read(uint16_t addr);
