#include "resources.h"



uint16_t sign_extend(uint16_t x, int bit_count)
{
	if((x >> (bit_count - 1)) & 1)
	{
		x |= (0xFFFF << bit_count);
	}

	return x;
}



void update_flags(uint16_t reg)
{
	if (registers[reg] == 0)
	{
		reg[R_COND] = FL_ZRO;
	}

	else if (registers[reg] >> 15)
	{
		reg[R_COND] = FL_NEG;
	}

	
	else	
	{
		reg[R_COND] = FL_POS;
	}

	return;
}



void trap(uint16_t instr)
{
	switch (instr)
	{
		case TRAP_GETC:
			puts();
			break;

		case TRAP_OUT:
			break;

		case TRAP_PUTS:
			break;

		case TRAP_IN:
			break;

		case TRAP_PUTSP:
			break;

		case TRAP_HALT:
			break;
	}	
}
