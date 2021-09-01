#ifdef __CYGWIN__

#include <Windows.h>
#include <conio.h>

DWORD fdwMode, fdwOldMode;

#endif
#if unix || __unix || __unix__

#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

struct termios original_tio;

struct termios original_tio;
#endif

/* implementations are platform dependent but signatures are not */
uint16_t check_key();
void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
