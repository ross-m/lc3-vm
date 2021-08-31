#include "resources."

void _add(uint16_t instr)
{
	/* destination address */
	uint16_t R0 = (instr >> 9) & 0x7;

	/* retrieve first value */
	uint16_t R1 = (instr >> 6) & 0x7;	

	/* immediate vs register mode */
	int mode = (instr >> 5) & 0x1;

	/* immediate mode */
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



void _and(uint16_t instr)
{
}



void _ldi(uint16_t instr)
{
	/* destination address */
	uint16_t R0 = (instr >> 9) & 0x7;

	/* compute intermediate address */
	uint16_t addr = registers[R_PC] + sign_extend((instr & 0x1FF), 9);

	/* read the address stored in the intermediate address */
	registers[R0] = mem_read(addr);

	update_flags(R0);

	return;
}
