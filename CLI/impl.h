#ifndef _IMPL_H_
#define _IMPL_H_

#include <stdint.h>

#define WHITESPACE " \t\r\n"
#define MAXBUF 256
#define MAXARGS 256

extern uint8_t clibuf[256];
extern uint8_t screenwidth;
extern uint8_t screenheight;

/* cli.c */
void cli_dispatch(char *buf);
void cli_about(int argc, char *argv[]);
void cli_help(int argc, char *argv[]);

/* term.c */
void cli_screen(int argc, char* argv[]);
void cli_cls(int argc, char* argv[]);
void cli_esc(int argc, char* argv[]);
void cli_ascii(int argc, char* argv[]);

/* time.c */
void cli_time(int argc, char* argv[]);

#endif