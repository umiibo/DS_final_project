#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "backprop.h"
#include "display.h"
#include "file.h"

int keyboard[ALPHBET] = {UNUSED};
int b_status[GUESSTURNS][LENGTH] = {UNUSED};
int numIn = 0;
int guess_turn;
char **board = NULL;
char *input = NULL;
char *puzzle = NULL;
FILE* fptr;
// FILE* dataptr;

int tmp = 0;

int main(){
    board = (char**)malloc(sizeof(char*)*GUESSTURNS);
    for(int t = 0;t < 6;t++){
        board[t] = (char*)malloc(sizeof(char)*LENGTH);
    }
    input = (char*)malloc(sizeof(char*)*LENGTH);
    puzzle = (char*)malloc(sizeof(char*)*LENGTH);

    fptr = open_library(fptr);
    // fptr = tidy_up(fptr);
    
    do{
        printf("New Quiz!\n");
        // init
        for(int t = 0;t < 6;t++){
            memset(board[t], 0, sizeof(char)*LENGTH);
        }
        memset(input, 0, sizeof(char)*LENGTH);
        memset(puzzle, 0, sizeof(char)*LENGTH);
        guess_turn = 0;

        // Pick a word for puzzle
        pick_puzzle(fptr,puzzle);

        print_Board(board, b_status);
        print_KB(keyboard);
        
        for(int turns = 0; turns < 6;turns++){
            guess_turn++;
            
            input = board[turns];
            feed_input(input);

            // if(!detect_guess(puzzle, input)){break;}

            print_Board(board, b_status);
            print_KB(keyboard);

        }

        printf("You guess %d times!\n\n\n", guess_turn);
        // save_data(dataptr, puzzle, guess_time);
        tmp++;
    }while(tmp < 3);

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
            }
        }

        if(numIn != 5){
            printf("\033[31m[Error]Please enter a word with 5 letters.\033[m\n");
        }
    }while(numIn != 5);
}

int detect_guess(char* answer, char* guess){
    /*Function 1 偵測答案與猜測
    比對answer與guess
    Example (Answer => apple)(guess => aeflp)
    b_status[0][0] = CORRECT;
    b_status[0][1] = WRONGSPOT;
    ...
    <本來想說比較的時候可以用Queue之類的，但是好像有點多此一舉，所以就單純一個個字母比對應該就豪ㄌ>
    可以先從guess[0]開始抓，然後跟answer的字母一對一比較，遇到CORRECT就可以換guess[1]繼續比...之類ㄉ(?)
    */

    /*Function 2 更改keyboard 顯示
    Global keyboard[]
    若無此字母則將該字母於keyboard裡的屬性設為NONEXIST
    若有此字母但位置不正確則設屬性為WRONGSPOT
    若字母正確且位置也正確則設為CORRECT

    Example (Answer => apple)(guess => aeflp)
    keyboard[ guess[0] - 'a' ] = CORRECT
    ...
    若猜測正確則return 0, 反之return 1 */
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

FILE* save_data(FILE* dfp, char* vocabulary, int guessNum){
    /*Function 1 儲存單字與猜數
    <用Linked-list、Stack、Queue之類ㄉ都可以!>
    node裡面包含的資料有：
        char 單字[5]
        int 猜數
        其他像top、或資料結構要用到ㄉ東西...
    */
    
    /*Function 2 開檔寫檔
    <可以先直接寫成會覆蓋原檔案就好，我研究一下搜尋要怎麼寫owo>
    方便檢查資料有沒有存錯之類的
    建一個檔案來檢視每次遊玩的紀錄
    */ 
   return dfp;
}

void clearup(){
    free(board);
    free(input);
    free(puzzle);
}
