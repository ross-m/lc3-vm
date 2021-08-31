#include "resources.h"

void puts()
{
	uint16_t* c = main_memory + registers[R_R0];

	while (*c)
	{
		putc((char)*c, stdout);
		++c;
	}

	fflush(stdout);

	return;
}
