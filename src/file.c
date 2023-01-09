#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
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

FILE* write_file(NODE* top, FILE* dfp){
    typedef struct record_t{
        int guess_time;
        char voc[LENGTH];
    }RECORD;
    RECORD temp;

    // file process
    if(!(dfp = fopen("record.csv.","r+"))){
        printf("File could not be open.");
        exit(EXIT_FAILURE);
    }else{
        printf("Open record successfully.\n");
    }

    // construct trie
    Trie *root = trieCreate();

    char *buffer = (char*)malloc(sizeof(char)*100);
    char buffer2[100];
    fscanf(dfp,"%s",buffer);
    fscanf(dfp,"%s",buffer2);

    int order = 0;
    while(!feof(dfp)){
        fscanf(dfp,"%[^,],%d\n",temp.voc,&temp.guess_time);
        trieInsert(root, temp.voc,temp.guess_time,order);
        order++;
    }

    // update file
    do{
        int result = trieSearch(root,top->voc);

        if(!result){
            fprintf(dfp, "%s, %d\n" , top->voc, top->turn);
            printf("In the file order[%d]", result);
        }else{
            printf("Have this word[%d].\n", result);

            rewind(dfp);
            fscanf(dfp,"%s",buffer);
            fscanf(dfp,"%s",buffer2);

            fseek(dfp, result*(SIZEOF_LINE_IN_FILE+1)+1, SEEK_CUR);
            fscanf(dfp,"%[^,],%d\n", temp.voc, &temp.guess_time);
            temp.guess_time = (temp.guess_time + top->turn) / 2;
            
            fseek(dfp, -(SIZEOF_LINE_IN_FILE+1), SEEK_CUR);
            fprintf(dfp, "%s, %d\n" , temp.voc, temp.guess_time);
        }
        top = top->next;
    }while(top != NULL);

    return dfp;
}



Trie *trieCreate()
{
    Trie *newNode = malloc(sizeof(Trie));

    int i;
    for (i = 0; i < ALPHBET; i++)
    {
        newNode->kids[i] = NULL;
    }

    newNode->isLeaf = false;
    return newNode;
}

void trieInsert(Trie *obj, char word[LENGTH],int gtime, int key)
{
    int index;
    int i;
    // printf("Insert %s into trie.\n", word);
    for (i = 0; i < LENGTH; i++)
    {
        index = word[i] - 'a';
        if (!obj->kids[index])
        {
            obj->kids[index] = trieCreate();
        }

        obj = obj->kids[index];
    }

    obj->guess_order[0] = gtime;
    obj->guess_order[1] = key;

    obj->isLeaf = true;
}

int trieSearch(Trie *obj, char word[LENGTH])
{
    int index;

    for (int i = 0; i < LENGTH; i++)
    {
        index = word[i] - 'a';

        if (!obj->kids[index])
        {
            return false;
        }

        obj = obj->kids[index];
    }
    
    return obj->guess_order[1];
}
