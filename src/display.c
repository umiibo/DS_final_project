#include<stdio.h>
#include<stdlib.h>
#include "display.h"


void print_Board(char** word){
    for(int c = 0; c < 6;c++){
        printf("---------------------\n|");
        for(int r = 0; r < 5;r++){
            printf(" %c |",word[c][r]);
        }
        printf("\n");
    }
}

void print_KB(int kb[]){
    int alph[26] = {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M'};
    printf("---------------------\n");
    for(int i = 0; i < 26;i++){
        if(i == 10){
            printf("\n ");
        }else if(i == 19){
            printf("\n    ");
        }

        if(kb[alph[i]-'A'] == UNUSED){
            printf("%c ",alph[i]);
        }else if(kb[alph[i]-'A'] == NONEXIST){
            printf("\033[30m%c\033[m ",alph[i]);
            printf(" ");
        }else if(kb[alph[i]-'A'] == WRONGSPOT){
            printf("\033[33m%c\033[m ",alph[i]);
            printf(" ");
        }else if(kb[alph[i]-'A'] == CORRECT){
            printf("\033[32m%c\033[m ",alph[i]);
        }
        // printf("%d ",kb[alph[i] - 'A']);
    }
    printf("\n");
    printf("---------------------\n");
}
