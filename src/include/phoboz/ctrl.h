#ifndef Ctrl_H
#define Ctrl_H

#include "SDL.h"

#define PRESS_RIGHT 1
#define PRESS_LEFT 2
#define PRESS_UP 4
#define PRESS_DOWN 8
#define PRESS_JUMP 16
#define PRESS_ATTACK 32
#define PRESS_ENTER 64
#define PRESS_ESC 128
#define SET_BITS(x,bits) (x|bits)
#define RESET_BITS(x,bits) (x&~bits)

extern int input;

extern int get_input(void);
extern int get_input_keydown(int ks);
extern int get_input_keyup(int ks);

#endif

