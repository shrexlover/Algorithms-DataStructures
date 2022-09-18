#include <stdio.h>
#include <minwindef.h>
#include <stdlib.h>
#include <string.h>
#include <sysinfoapi.h>
#include <stdbool.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))


struct Node {
    int key;
    char name[13];
    char sname[13];
    struct Node *left;
    struct Node *right;
    int height;
};


int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}


struct Node *newNode(int key, char tname[13], char tsurname[13]) {
    struct Node *node = malloc(sizeof(struct Node));
    node->key = key;
    strcpy(node->name,tname);
    strcpy(node->sname, tsurname);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}


struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Node *insertNode(struct Node *node, int key, char name[13], char sname[13]) {
    if (node == NULL)
        return (newNode(key, name, sname));

    if (key < node->key)
        node->left = insertNode(node->left, key, name, sname);
    else if (key > node->key)
        node->right = insertNode(node->right, key, name, sname);
    else
        return node;


    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}
bool Search(struct Node *BSTroot, int key) {
    if (BSTroot == NULL) { return false; }
    if (BSTroot->key == key) { return true; }
    else if (key <= BSTroot->key) { return Search(BSTroot->left, key); }
    else { return Search(BSTroot->right, key); }
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;


    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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

    char line[40];
    struct Node *root;
    fgets(line, sizeof line, file);
    sscanf(line, "%s %s %s", tname, tsname, tidx);
    root = newNode(atoi(tidx), tname, tsname);

    while(fgets(line, sizeof line, file)){
        sscanf(line, "%s %s %s", tname, tsname, tidx);
        insertNode(root, atoi(tidx), tname, tsname);
    }

    insertNode(root, 5261893, "hdwdqakjh", "efndlfpk");
    deleteNode(root, 4875342);
    fclose(file);
    return 0;
}
