#include<stdio.h>
#include<stdlib.h>
#include "file.h"

FILE* open_library(FILE* fp){
    if(!(fp = fopen("word.txt","r"))){
        printf("Fail to open the file.\n");
    }else{
        printf("Open the file successfully.\n");
    }
    return fp;
}
