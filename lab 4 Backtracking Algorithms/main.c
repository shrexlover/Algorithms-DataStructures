#include<stdio.h>
#include<stdlib.h>

#define V 100

void printSolution(int path[]);

int isSafe(int v, int **graph, int path[], int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return 0;
    int i;
    for (i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}


int hamCycleUtil(int **graph, int path[], int pos) {

    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }
    int v;
    for (v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamCycleUtil(graph, path, pos + 1) == 1)
                return 1;

            path[pos] = -1;
        }
    }

    return 0;
}

int hamCycle(int **graph, int num_of_V) {
    int *path = malloc(sizeof(num_of_V));
    int i;
    for (i = 0; i < V; i++)
        path[i] = -1;
    path[0] = 0;
    if (hamCycleUtil(graph, path, 1) == 0) {
        printf("\nSolution does not exist");
        return 0;
    }

    printSolution(path);
    return 1;
}

void initgraph(int **arr) {
    int i, j;
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            arr[i][j] = 0;

}

void addEdgegraph(FILE* file, int **arr) {
    char line[5];
    while(fgets(line, 5, file)) {
        char *a = NULL;
        char *b = NULL;
        scanf(line, "%s %s", a, b);
        int i = atoi(a);
        int j = atoi(b);
        arr[i][j] = 1;
        arr[j][i] = 1;
    }
}

struct stack{
    int value;
    struct stack *next;
};

struct stack *add_stack(struct stack *head, int value){
    struct stack *x = malloc(sizeof(*x));
    x->value = value;
    x->next = head;
    return x;
}

struct stack *pop (struct stack *head){
    if(head == NULL)
        return NULL;
    struct stack *tmp = head->next;
    free(head);
    return tmp;
}
int nbh(int **graph, int vertex, int n){
    for (int i = 0; i < n; ++i) {
        if (graph[vertex][i] != 0){
            return i;
        }
    }
    return -1;
}

void eulerian_circut(int **graph, int n){
    struct stack *path = NULL;
    struct stack *stos = NULL;
    stos = add_stack(stos, 0);
    while (stos != NULL) {
        int current = stos -> value;
        int next = nbh(graph, current, n);
        if (next == -1){
            path = add_stack(path, current);
            stos = pop(stos);
        }
        else{
            stos = add_stack(stos, next);
            graph[current][next] = 0;
            graph[next][current] = 0;
        }
    }

}

int is_even (int **graph, int n){
    int counter;
    for (int i=0;i<n;i++){
        counter = 0;
        for (int j=0;j<n;j++)
            if (graph[i][j] == 1)
                counter++;
        if (counter%2 == 1)
            return 0;

    }
    return 1;
}
void adding (int x, int *set, int **graph, int n){
    set[x] = 1;
    for (int i=0;i<n;i++){
        if (graph[x][i] == 1 && set[i] == 0){

            adding(i,set,graph,n);
        }
    }
}

int is_connected (int **graph, int n){
    int set[n];
    for (int i=0;i<n;i++)
        set[i] = 0;
    adding(0, set, graph, n);
    for (int i=0;i<n;i++){
        if (set[i] == 0){
            printf("%d\n",i);
            return 0;
        }
    }

    return 1;
}
int main() {
    FILE *file = fopen("graph", "r");
    int **graph1;
    initgraph(graph1);
    addEdgegraph(file, graph1);
    is_connected(graph1, 100);
    is_even(graph1, 100);
    eulerian_circut(graph1, 100);
    hamCycle(graph1, 100);
    fclose(file);
    return 0;
}