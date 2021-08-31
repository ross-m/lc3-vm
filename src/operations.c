#include "resources.h"

void _add(uint16_t instr)
{
	/* destination address */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* retrieve first value */
	uint16_t r0 = (instr >> 6) & 0x7;	

	/* immediate vs register mode */
	uint16_t mode = (instr >> 5) & 0x1;

	/* immediate mode */
	if (mode)
	{
		uint16_t imm5 = sign_extend(instr & 0x1F, 5);
		registers[r0] = registers[r0] + imm5;
	}
	
	else 
	{
		uint16_t r2 = instr & 0x7;
		registers[r0] = registers[r0] + registers[r2];
	}

	update_flags(r0);

	return;
}



void _and(uint16_t instr)
{
	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* first value */
	uint16_t r1 = (instr >> 6) & 0x7;

	/* register vs immediate mode */
	uint16_t mode = instr >> 5;	

	/* immediate mode */
	if (mode) 
	{
		uint16_t imm5 = sign_extend(instr & 0x1F, 5);
		registers[r0] = registers[r1] & imm5;
	}

	else
	{
		uint16_t r2 = instr & 0x7;
		registers[r0] = registers[r1] & registers[r2]; 
	}

	update_flags(r0);

	return;		
}



void _br(uint16_t instr)
{
	uint16_t cond_codes = (instr >> 9) & 0x7;

	if (cond_codes & registers[R_COND])
	{
		registers[R_PC] += sign_extend(instr & 0x1FF, 9);
	}

	return;
}



/* also handles the RET call */
void _jmp(uint16_t isntr)
{
	/* base register */
	uint16_t baseR = (instr >> 6) & 0x7;
 
	registers[R_PC] = mem_read(baseR);

	return;
}



void _jsr(uint16_t instr)
{
	/* save calling routine */
	registers[R_R7] = registers[R_PC]

	/* location of first instruction */
	uint16_t flag = (instr >> 11) & 0x1;

	if (flag)
	{
		registers[R_PC] += sign_extend((instr & 0x7FF), 11);
	}
	
	else
	{
		uint16_t r1 = (instr >> 6) & 0x7;

		registers[R_PC] = registers[r1];
	}

	return;
}



void _ld(uint16_t instr)
{
	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* offset from program counter */
	uint16_t pcoffset = sign_extend(instr & 0x1FF, 9);	

	/* load value into destination address */
	registers[r0] = mem_read(registers[R_PC] + pcoffset);

	update_flags(r0);

	return;
}



void _ldi(uint16_t instr)
{
	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* compute intermediate address */
	uint16_t addr = registers[R_PC] + sign_extend((instr & 0x1FF), 9);

	/* read the address stored in the intermediate address */
	registers[r0] = mem_read(addr);

	update_flags(r0);

	return;
}



void _ldr(uint16_t instr)
{ 
	/* offset from base register */
	uint16_t reg_offset = sign_extend(instr & 0x3F, 6);

	/* base register */
	uint16_t r1 = (instr >> 6) & 0x7;

	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x9;

	registers[r0] = mem_read(registers[r1] + reg_offset);

	update_flags(r0);

	return;
}



void _lea(uint16_t instr)
{
	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* offset from pc */
	uint16_t pcoffset = sign_extend(instr & 0x1FF, 9);

	registers[r0] = registers[R_PC] + pcoffset;

	update_flags(r0);

	return;
}



void _not(uint16_t instr)
{
	/* destination register */
	uint16_t r0 = (instr >> 9) & 0x7;

	/* source register */
	uint16_t r1 = (instr >> 6) & 0x7;

	registers[r0] = ~registers[r1];

	update_flags(r0);
}



void _st(uint16_t instr)
{
	/* destination address */
	uint16_t addr = registers[R_PC] + sign_extend(instr & 0x1FF, 9);

	/* source register */
	uint16_t r0 = (instr >> 9) & 0x7;

	mem_write(addr, r0);

	return;
}



void _sti(uint16_t instr)
{
	/* destination address */
	uint16_t addr = mem_read(registers[R_PC] + sign_extend(instr & 0x1FF, 9));

	/* source register */
	uint16_t r0 = (instr >> 9) & 0x7;

	mem_write(addr, registers[r0]);

	return;	
}



void _str(uint16_t instr)
{
	/* base register */
	uint16_t r0 = (instr >> 6) & 0x7;

	/* destination address */
	uint16_t addr = registers[r0] + sign_extend(instr & 0x3F, 6);

	/* source register */
	uint16_t r1 = (instr >> 9) & 0x7;

	mem_write(addr, registers[r1]);

	return;
}
