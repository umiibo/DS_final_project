#ifndef __FILE_H__
#define __FILE_H__


#define SIZEOF_LINE_IN_FILE 8
struct node{
    int turn;
    char voc[5];
    struct node *next;
};
typedef struct node NODE;

typedef struct trie_t{
    union{
        struct trie_t *kids[ALPHBET];
        int guess_order[2];
    };
    bool isLeaf;
}Trie;


FILE* open_library(FILE* fp);
FILE* write_file(NODE* top, FILE* dfp);
Trie *trieCreate();
void trieInsert(Trie *obj, char word[LENGTH],int gtime, int index);
int trieSearch(Trie *obj, char word[5]);
#endif
