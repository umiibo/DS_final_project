#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "backprop.h"
#include "file.h"

FILE* open_library(FILE* fp){
    if(!(fp = fopen("martin.txt","r+"))){
        printf("Fail to open the file.\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Open the file successfully.\n");
        return fp;
    }
}

FILE* tidy_up(FILE* fplib){
    char* buffer;
    buffer = (char*)malloc(sizeof(char)*LENGTH);

    // if(!(fplib = fopen("martin.txt","r"))){
    //     // printf("Fail to open the file.\n");
    // }else{
    //     // printf("Open the file successfully.\n");
    // }
    
    // rewind(fplib);
    // srand(time(NULL));
    // int order = rand() % 1003;
    fseek(fplib,3,SEEK_SET);
    fseek(fplib, 3 * (sizeof(char)*5), SEEK_CUR);

    fscanf(fplib, "%s", buffer);

    printf("%s\n",buffer);

    return fplib;
}
