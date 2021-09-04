#include "../include/resources.h"

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
	
	return;
}



void _putsp()
{
	uint16_t* c = main_mem + registers[R_R0];

	while (*c)
	{
		char char1 = (*c) & 0xFF;
		putc(char1, stdout);
		char char2 = (*c) >> 8;
		if (char2) putc(char2, stdout);
		++c;
	}

	fflush(stdout);

	return;
}




