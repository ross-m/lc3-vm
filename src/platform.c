#include "../include/resources.h"
#include "../include/platform.h"

#if __CYGWIN__ || WIN32 || WIN64

DWORD fdwMode, fdwOldMode;

uint16_t check_key()
{
	return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}



void disable_input_buffering()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdin, &fdwOldMode); /* save old mode */
	fdwMode = fdwOldMode
	    ^ ENABLE_ECHO_INPUT  /* no input echo */
	    ^ ENABLE_LINE_INPUT; /* return when one or
				    more characters are available */
	SetConsoleMode(hStdin, fdwMode); /* set new mode */
	FlushConsoleInputBuffer(hStdin); /* clear buffer */

	return;
}



void restore_input_buffering()
{
    SetConsoleMode(hStdin, fdwOldMode);

    return;
}

#endif
#if __unix__ || __unix || unix || __OSX__ || __APPLE__

uint16_t check_key()
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	return select(1, &readfds, NULL, NULL, &timeout) != 0;
}



void disable_input_buffering()
{
	tcgetattr(STDIN_FILENO, &original_tio);
	struct termios new_tio = original_tio;
	new_tio.c_lflag &= ~ICANON & ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	return;
}



void restore_input_buffering()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);

	return;
}

#endif

void handle_interrupt(int signal)
{
	restore_input_buffering();
	printf("\n");
	exit(-2);
}
