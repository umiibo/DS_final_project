#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "backprop.h"

enum keyboard_status_t{
    UNUSED, NONEXIST, WRONGSPOT, CORRECT
};

void print_Board(char** word, int status[GUESSTURNS][LENGTH]);
void print_KB(int kb[]);
#endif
