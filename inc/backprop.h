#ifndef __BACKPROP_H__
#define __BCAKPROP_H__

#define LENGTH 5
#define GUESSTURNS 6
#define ALPHBET 26

void feed_input(char* container);
void pick_puzzle(FILE* fp, char* answer);
FILE* save_data(FILE* dfp, char* vocabulary, int guessNum);
void clearup();

#endif
