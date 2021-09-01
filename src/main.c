#include "resources.h"
#include "platform.h"

void mem_write(uint16_t addr, uint16_t val)
{
	main_mem[addr] = val;
	return;
}



uint16_t mem_read(uint16_t addr)
{
	if (addr == MR_KBSR)
	{
		if (check_key())
		{
			main_mem[MR_KBSR] = (1 << 15);
			main_mem[MR_KBDR] = getchar();
		}

		else
		{
			main_mem[MR_KBSR] = 0;
		}
	}

	return main_mem[addr];
}



uint16_t swap16(uint16_t x)
{
	return (x << 8) | (x >> 8);
}



void read_image_file(FILE* f)
{
	uint16_t start;
	fread(&start, sizeof(start), 1, f);
	start = swap16(start);

	uint16_t max_size = UINT16_MAX - start; // Shouldn't this be sizeof(start)?
	uint16_t* p = main_mem + start;
	size_t read = fread(p, sizeof(uint16_t), max_size, f);

	while (read-- > 0)
	{
		*p = swap16(*p);
		++p;
	}

	return;
}



int read_image(const char* image_path)
{
	FILE* file = fopen(image_path, "rb");

	if (!file) 
	{
		return 0;
	}
	
	read_image_file(file);
	fclose(file);

	return 1;
}



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
       		registers[R_COND] = FL_ZRO;
       }

       else if (registers[reg] >> 15)
       {
       		registers[R_COND] = FL_NEG;
       }

       else	
       {
       		registers[R_COND] = FL_POS;
       }

       return;
}



uint16_t trap(uint16_t instr)
{
	uint16_t running = 1;

	switch (instr)
	{
		case TRAP_GETC:
			_getc();
			break;

		case TRAP_OUT:
			_out();
			break;

		case TRAP_PUTS:
			_puts();
			break;

		case TRAP_IN:
			_in();
			break;

		case TRAP_PUTSP:
			_putsp();
			break;

		case TRAP_HALT:
			_halt();
			running = 0;
			break; 
	}	

	return running;
}



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("lc3 [image-file1] ...\n");
		exit(2);
	}

	/* load programs into simulated memory space */
	for (int i = 1; i < argc; ++i)
	{
		if(!read_image(argv[i]))
		{
			printf("failed to load image: %s\n", argv[i]);
			exit(1);
		}
	}

	/* platform-dependent configuration */
	signal(SIGINT, handle_interrupt);
	disable_input_buffering();

	/* set PC to beginning of instruction array */ 
	enum { PC_START_LOCATION = 0x3000 };
	registers[R_PC] = PC_START_LOCATION;

	/* main execution loop */
	int running = 1;

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
				_and(instruction);
				break;

			case OP_NOT:
				_not(instruction);
				break;

			case OP_BR:
				_br(instruction);
				break;
		
			case OP_JMP:
				_jmp(instruction);
				break;

			case OP_JSR:
				_jsr(instruction);
				break;

			case OP_LD:
				_ld(instruction);
				break;

			case OP_LDI:
				_ldi(instruction);
				break;

			case OP_LDR:
				_ldr(instruction);
				break;

			case OP_LEA:
				_lea(instruction);
				break;

			case OP_ST:
				_st(instruction);
				break;

			case OP_STI:
				_sti(instruction);
				break;

			case OP_STR:
				_str(instruction);
				break;

			case OP_TRAP:
				trap(instruction & 0xFF);
				break;

			case OP_RES:
				break;

			case OP_RTI:
				break;

			default: 	
				abort();
				break;
		}
	}
	
	restore_input_buffering();

	return 0;
}
