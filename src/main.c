#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "backprop.h"
#include "display.h"
#include "file.h"

NODE* save_data(NODE* top, char* vocabulary, int guessNum);

int keyboard[ALPHBET] = {UNUSED};
int b_status[GUESSTURNS][LENGTH] = {UNUSED};
int numIn = 0;
int guess_turn;
char **board = NULL;
char *input = NULL;
char *puzzle = NULL;
FILE* fptr;
FILE* dataptr;
NODE *head = NULL;

int tmp = 0;

int main(){
    board = (char**)malloc(sizeof(char*)*GUESSTURNS);
    for(int t = 0;t < 6;t++){
        board[t] = (char*)malloc(sizeof(char)*LENGTH);
    }
    input = (char*)malloc(sizeof(char*)*LENGTH);
    puzzle = (char*)malloc(sizeof(char*)*LENGTH);

    fptr = open_library(fptr);

    
    do{
        printf("New Quiz!\n");
        // init
        for(int i = 0;i<ALPHBET;i++){
            keyboard[i] = UNUSED;
        }
        for(int t = 0;t < 6;t++){
            memset(board[t], 0, sizeof(char)*LENGTH);
        }
        memset(input, 0, sizeof(char)*LENGTH);
        memset(puzzle, 0, sizeof(char)*LENGTH);
        guess_turn = 0;

        // Pick a word for puzzle
        pick_puzzle(fptr,puzzle);
        // puzzle = "nurse";

        print_Board(board, b_status);
        print_KB(keyboard);
        
        for(int turns = 0; turns < 6;turns++){
            guess_turn++;
            input = board[turns];
            feed_input(input);

            if(!detect_guess(puzzle, input)){
                
                print_Board(board, b_status);
                print_KB(keyboard);
                break;
            }

            
            print_Board(board, b_status);
            print_KB(keyboard);

            if(guess_turn == 6){guess_turn=0;}

        }

        if(guess_turn == 0){
            printf("Sorry, you didn't get the right answer.\n");
            printf("The answer is:%s\n\n\n",puzzle);
        }else{
            printf("You guess %d times!\n\n\n", guess_turn);
        }
        head = save_data(head, puzzle, guess_turn);
        tmp++;
    }while(1);

    printf("writing file...\n");
    dataptr = write_file(head,dataptr);

    fclose(dataptr);
    fclose(fptr);
    clearup();
    printf("Execute successfully.\n");
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
            }else if(c == '0'){
                printf("Exit.\n");
                exit(EXIT_SUCCESS);
            }
        }

        if(numIn != 5){
            printf("\033[31m[Error]Please enter a word with 5 letters.\033[m\n");
        }
    }while(numIn != 5);
}

int detect_guess(char* answer, char* guess){
    bool answerFlags[LENGTH] = {false,false,false,false,false};
    int clue[LENGTH] = {NONEXIST,NONEXIST,NONEXIST,NONEXIST,NONEXIST};
    
    for(int i = 0;i<LENGTH;i++){
        b_status[guess_turn-1][i] = clue[i];
        keyboard[guess[i]-'a'] = NONEXIST;
    }
    // guess
    for(int i=0 ; i < LENGTH ; i++){
        if(guess[i] == answer[i]){
            clue[i] = CORRECT;
            keyboard[guess[i]-'a'] = CORRECT;
            answerFlags[i] = true;
        }
    }

    //
    for(int i=0 ; i<LENGTH ; i++){
        if(clue[i] == NONEXIST){
            for(int j=0 ; j<LENGTH ;j++){
                if(guess[i] == answer[j] && !answerFlags[j]){
                    clue[i] = WRONGSPOT;
                    keyboard[guess[i]-'a'] = WRONGSPOT;
                    answerFlags[j] = true;
                    break;
                }
            }
        }
    }

    for(int i=0 ; i<LENGTH ; i++){
        b_status[guess_turn-1][i] = clue[i];
    }

    if (clue[0] == CORRECT && clue[1] == CORRECT && clue[2] == CORRECT && clue[3] == CORRECT && clue[4] == CORRECT){
        return 0;
    }
    else{
        return 1;
    }

    return 0;
}

void pick_puzzle(FILE* fp, char* answer){
    rewind(fp);
    srand(time(NULL));
    int order = rand() % 1003;
    fseek(fp, 3,SEEK_SET);
    fseek(fp, order * (sizeof(char)*LENGTH + 1), SEEK_CUR);
    fscanf(fp,"%s",answer);
    printf("word:%s\n",answer);
}

NODE* save_data(NODE* top, char* vocabulary, int guessNum){
    NODE *temp;
    temp = (NODE*)malloc(sizeof(NODE));

    temp->turn = guessNum;
    for(int i = 0;i<LENGTH;i++){
        temp->voc[i] = vocabulary[i];
    }
    temp->next = top;
    top = temp;

    return top;
}

void clearup(){
    free(board);
    free(input);
    free(puzzle);
}
