#ifdef __CYGWIN__ || WIN32 || WIN64

#include <Windows.h>
#include <conio.h>


#endif
#ifdef unix || __unix || __unix__

#include <unistd.h>
#include <sys/time.h>
#include <sys/termios.h>

struct termios original_tio;

#endif

/* implementations are platform dependent but signatures are not */
uint16_t check_key();
void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
