#include<stdio.h>
#include<stdlib.h>
#include "display.h"
#include "file.h"

void feed_input(char* container);
void clearup();

int keyboard[26] = {UNUSED};
int numIn = 0;
char **board = NULL;
char *input = NULL;
char *puzzle = NULL;
FILE* fptr;

int main(){
    board = (char**)malloc(sizeof(char*)*6);
    for(int t = 0;t < 6;t++){
        board[t] = (char*)malloc(sizeof(char)*5);
    }
    input = (char*)malloc(sizeof(char*)*5);
    puzzle = (char*)malloc(sizeof(char*)*5);

    fptr = open_library(fptr);
    
    // Pick a word for puzzle
    // pick_puzzle();

    print_Board(board);
    print_KB(keyboard);
    
    for(int turns = 0; turns < 6;turns++){
        feed_input(board[turns]);

        // if(!detect_guess(puzzle, input)){
        //     break;
        // }

        // display input
        // printf("Your Input:");
        // for(int j = 0;j < 5;j++){   
        //     putchar(board[turns][j]);
        //     printf(" ");
        // }
        // printf("\n# of Input:%d\n",numIn);

        print_Board(board);
        print_KB(keyboard);
    }
    
    printf("Execute successfully.\n");
    fclose(fptr);
    clearup();
    return 0;
}

void feed_input(char* container){
    char c;
    do{
        numIn = 0;
        printf("Please enter your guess:");

        while((c = getchar()) !='\n'){
            if((c >= 'a' && c <= 'z')){
                container[numIn] = c;
                numIn++; 
            }
        }

        if(numIn != 5){
            printf("\033[31m[Error]Please enter a word with 5 letters.\033[m\n");
        }
    }while(numIn != 5);
}

int detect_guess(char* answer, char* guess){
    // Global keyboard[]
    // 若無此字母則將該字母於keyboard裡的屬性設為NONEXIST
    // 若有此字母但位置不正確則設屬性為WRONGSPOT
    // 若字母正確且位置也正確則設為CORRECT

    // Example (Answer => apple)(guess => aeflp)
    // keyboard[ guess[0] - 'a' ] = CORRECT
    // ...
    // 若猜測正確則return 0, 反之return 1
}

void pick_puzzle(FILE* fp, char* answer){
    // 從word.txt內隨機找一行當作題目存進answer裡
    // extra func -> 若連續選到重覆的單字則重選一題
}

void clearup(){
    free(board);
    free(input);
    free(puzzle);
}
