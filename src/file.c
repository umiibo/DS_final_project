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
    
    return fplib;
}
