#include "resources.h"

void _getc()
{
	registers[R_R0] = (uint16_t)getchar();

	return;
}



void _out()
{
	putc((char)registers[R_R0], stdout);
	fflush(stdout);

	return;
}



void _puts()
{
	uint16_t* c = main_mem + registers[R_R0];

	while (*c)
	{
		putc((char)*c, stdout);
		++c;
	}

	fflush(stdout);

	return;
}



void _in()
{
	printf("Enter: ");
	char c = getchar();
	putc(c, stdout);
	registers[R_R0] = (uint16_t)c;
	fflush(stdout);
	
	return;
}



void _putsp()
{
	uint16_t* c = main_mem + registers[R_R0];

	while (*c)
	{
		putc((*c) & 0xFF, stdout);
		if ((*c) >> 8) putc((*c) >> 8, stdout);
		++c;	
	}

	fflush(stdout);

	return;
}



void _halt()
{
	puts("HALT");
	fflush(stdout);

	return;
}
