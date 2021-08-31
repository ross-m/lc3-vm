#include "resources."

void add(uint16_t instr)
{
	/* stores final value */
	uint16_t R0 = (instr >> 9) & 0x7;

	/* retrieve first value */
	uint16_t R1 = (instr >> 6) & 0x7;	

	/* immediate vs register mode */
	int mode = (instr >> 5) & 0x1;

	if (mode)
	{
		uint16_t imm5 = sign_extend(instr & 0x1F, 5);
		registers[R0] = registers[R1] + imm5;
	}
	
	else 
	{
		uint16_t R2 = instr & 0x7;
		registers[R0] = registers[R1] + registers[R2];
	}

	update_flags(R0);

	return;
}
