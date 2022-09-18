#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include <time.h>
#define MAX_LEN  100

struct Node{
    char name[13];
    char surname[13];
    int idx;
    struct Node *leftchild;
    struct Node *rightchild;
};

struct Node* BSTroot = NULL;

struct Node* getNewNode(int idx, char tname[13], char tsurname[13]){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->idx = idx;
    newNode->leftchild = newNode->rightchild = NULL;
    strcpy(newNode->name,tname);
    strcpy(newNode->surname, tsurname);
    return newNode;
}

struct Node* Insertion( struct Node *broot, int idx, char name[13], char surname[13] ){
    if (broot == NULL){
        return getNewNode(idx, name, surname);
    }
    else if ( idx < (broot->idx) ){
        if(broot->leftchild == NULL){
            broot->leftchild = getNewNode( idx, name, surname);
        }
        else{
            Insertion(broot->leftchild, idx, name, surname);
        }
    }
    else{
        if(broot->rightchild == NULL){
            broot->rightchild = getNewNode( idx, name, surname);
        }
        else{
            Insertion(broot->rightchild, idx, name, surname);
        }
    }
}
struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;

    while (current->leftchild != NULL)
        current = current->leftchild;

    return current;
}

bool Search(struct Node *BSTroot, int idx){
    if(BSTroot == NULL){return false;}
    if(BSTroot->idx == idx){return true;}
    else if(idx <= BSTroot->idx){return Search(BSTroot->leftchild, idx);}
    else {return Search(BSTroot->rightchild, idx);}
}
struct Node *deleteNode(struct Node *root, int idx) {
    // Find the node and delete it
    if (root == NULL)
        return root;

    if (idx < root->idx)
        root->leftchild = deleteNode(root->leftchild, idx);

    else if (idx > root->idx)
        root->rightchild = deleteNode(root->rightchild, idx);

    else {
        if ((root->leftchild == NULL) || (root->rightchild == NULL)) {
            struct Node *temp = root->leftchild ? root->leftchild : root->rightchild;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node *temp = minValueNode(root->rightchild);

            root->idx = temp->idx;

            root->rightchild = deleteNode(root->rightchild, temp->idx);
        }
    }
}

int main() {

    FILE *file = fopen("namelist", "r");
    if (file == NULL) {
        printf("no such file.");
        return 0;
    }

    char tname[13];
    char tsname[13];
    char tidx[8];

    char line[MAX_LEN];
    long long int begin = GetTickCount();
    struct Node *root;
    fgets(line, sizeof line, file);
    sscanf(line, "%s %s %s", tname, tsname, tidx);
    root = getNewNode(atoi(tidx), tname, tsname);

    while(fgets(line, sizeof line, file)){
        sscanf(line, "%s %s %s", tname, tsname, tidx);
        Insertion(root, atoi(tidx), tname, tsname);
    }

    long long int end = GetTickCount();
    Insertion(root, 5261893, "Eliha", "dhgkdKl");
    deleteNode(root, 5261893);
    double elapsed = (end - begin)*1e-3;
    printf("Time measured: %.3f seconds.\n", elapsed);
    fclose(file);
    free(BSTroot);

    return 0;
}