#ifndef _TERM_H_
#define _TERM_H_

void term_cursor_on(void);
void term_cursor_off(void);
void term_set_cursor_pos(int x, int y);
void term_delay(int ms);

#endif