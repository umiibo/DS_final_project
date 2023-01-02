#ifndef __DISPLAY_H__
#define __DISPLAY_H__

enum keyboard_status_t{
    UNUSED, NONEXIST, WRONGSPOT, CORRECT
};

void print_Board(char** word);
void print_KB(int kb[26]);
#endif
