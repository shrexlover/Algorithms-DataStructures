#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sysinfoapi.h>
typedef struct Node{
    char* name;
    char* sname;
    int idx;
    struct Node *child;
};
struct Node *Lroot = NULL;
struct Node* getNewNode(int idx, char *tname, char *tsurname){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->idx = idx;
    newNode->child = NULL;
    strcpy(newNode->name,tname);
    strcpy(newNode->sname, tsurname);
}
struct Node* insert(struct Node *root, char* name, char* sname, int idx){
    if (root == NULL){
        return getNewNode(idx, name, sname);
    }
    else{
        if(root->child == NULL){
            return root->child = getNewNode(idx, name, sname);
        }
        else{
            insert(root->child, name, sname, idx);
        }
    }
}
struct Node *deleteNode(struct Node *root, int idx) {
    if (root == NULL)
        return root;
    if(idx != root->idx){
        root->idx = deleteNode(root->child, idx);
    }
    else{
        if(root->child == NULL){
            struct Node *temp = root->child;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        }
        else{
            struct Node *temp = root->child;
            root->idx = temp->idx;

            root->child = deleteNode(root->child, temp->idx);
        }

    }
}

bool Search(struct Node *root, int idx) {
    if (root == NULL) { return false; }
    if (root->idx == idx) { return true; }
    else { return Search(root->child, idx); }
}
int main() {
    FILE *file = fopen("namelist.txt", "r");
    if (file == NULL) {
        printf("no such file.");
        return 0;
    }
    struct Node *root;
    char *tname;
    char *tsname;
    char *tidx;
    char *token;
    char line[40];
    long long int begin = GetTickCount64();
    while(fgets(line, 40, file)){
        int i;
        token = strtok(line, "\0");
        strcpy(tname,token);
        token = strtok(NULL, "\0");
        strcpy(tsname, token);
        token = strtok(NULL, "\0");
        strcpy(tidx, token);
        i = atoi(tidx);
        insert(&Lroot, i, tname, tsname);
    }
    Search(root, 5323908 );
    deleteNode(root, 2794739);
    long long int end = GetTickCount64();
    double elapsed = (end - begin)*1e-3;
    printf("Time measured: %.3f seconds.\n", elapsed);
    fclose(file);
    free(Lroot);

    return 0;
}
