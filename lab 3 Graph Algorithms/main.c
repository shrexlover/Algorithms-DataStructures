#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define ver 100



char *edge_list;
char* get_EL(FILE *file, char *edge_list0){
    char *line;
    while(fgets(line, 5, file)) {
        char *edge;
        char *v1 = strtok(line, " ");
        strcpy(edge, v1);
        char *v2 = strtok(NULL, " ");
        strcpy(edge, v2);
        strcpy(edge_list0, edge);
    }
    return edge_list0;
}

bool search_edge_list(char *edge_list1, int a, int b){
    int i;
    int n = (((100 * 99)/2) * 0.6);
    char *res_table;
    for(i = 0; i < n; i++){
        char *line = &edge_list1[i];
        int v1 = atoi(&line[0]);
        if(v1 == a){
            int v2 = atoi(&line[1]);
            if (v2 == b){
                char *yes = 1;
                strcpy(res_table, yes);
                //printf(("yes"));
                return true;
            }
        }   else{ return false;}
    }
    if(res_table == NULL){return false;}
}

 struct NodeAL{
    int num;
    struct NodeAL* nextNodeAL;
};

 struct Graph{
    int V;
    int* visited;
    struct NodeAL** NodeALlist;
};


//int *adress_book;
struct NodeAL * creatennodes(int v){
    struct NodeAL* NodeALlnew = malloc(sizeof(struct NodeAL));
    NodeALlnew->num = v;
    NodeALlnew->nextNodeAL = NULL;
    return NodeALlnew;

}

struct Graph* createAGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->V = vertices;

    graph->NodeALlist = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++)
        graph->NodeALlist[i] = NULL;
        graph->visited[i] = 0;

    return graph;
}


void addEdge(struct Graph* graph, int s, int d) {

    struct NodeAL* newNode = creatennodes(d);
    newNode->nextNodeAL = graph->NodeALlist[s];
    graph->NodeALlist[s] = newNode;

    newNode = creatennodes(s);
    newNode->nextNodeAL = graph->NodeALlist[d];
    graph->NodeALlist[d] = newNode;
}
struct Graph* get_edges_al(FILE *file, struct Graph* graph){
    char line[5];
    while(fgets(line, 5, file)){
        char *a = NULL;
        char* b = NULL;
        scanf(line, "%s %s", a, b);
        addEdge(graph, atoi(a), atoi(b));
    }
    return graph;
}

void initAM(int arr[][ver]) {
    int i, j;
    for (i = 0; i < ver; i++)
        for (j = 0; j < ver; j++)
            arr[i][j] = 0;

}

void addEdgeAM(FILE* file, int arr[][ver]) {
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
bool searchAM(int i, int j, int arr[][ver]){
    if (arr[i][j] == 1){
        return true;
    }
    else{
        return false;
    }
}
bool searchAL(struct NodeAL *head, int i){
    struct NodeAL *current = head;
    while (current != NULL){
        if (current->num == i)
            return 1;
        current = current->nextNodeAL;
    }
    return 0;
}
int inc_arr[100][2970];
int ed_no = 0;
void add_edge(FILE* file) {
    char line[5];
    while (fgets(line, 5, file)) {
        char *a = NULL;
        char *b = NULL;
        scanf(line, "%s %s", a, b);
        int u = atoi(a);
        int v = atoi(b);
        inc_arr[u][ed_no] = 1;
        inc_arr[v][ed_no] = 1;
        ed_no++;
    }
}
bool searchIM(int array[100][2970], int a, int b, int numE ){
    for(int i = 0; i < numE; i++){
        if(array[a][i] == 1){
            if(array[b][i] == 1){
                return true;
            }
        }
    }
    return 0;
}

//// ex 2 DAG
int* toposort; //initialize toposort - fill with -1
void inittoposort(int* arr){
    int i;
    for(i = 0; i < 100; i++){
        arr[i] = (-1);
    }
}
int append(int* array, int number){
    for(int i = 0; i < 100; i++){
        if(array[i] == (-1)){
            array[i] = number;
            return array;
        }
    }
}
void DFS(struct Graph* graph, int vertex) {
    struct NodeAL* adjList = graph->NodeALlist[vertex];
    struct NodeAL* temp = adjList;
    graph->visited[vertex] = 1;
    //printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->num;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        if(temp->nextNodeAL == NULL){
            append(toposort, connectedVertex);
        }
        temp = temp->nextNodeAL;

    }
}
void initVN(int* arr){
    for(int i = 0; i < 100; i++){
        arr[i] = 0;
    }
}

void topologicalsort(struct Graph* graph){
    int* visited_nodes;
    initVN(visited_nodes);
    inittoposort(toposort);
    for(int i = 0; i < 100; i++){
        if(visited_nodes[i]==0){
            DFS(graph, i);
        }
    }

}

int main() {
    /*for (int i = 1; i <= 100; i++){
        creatennodes(i);
    }*/
    struct Graph* graph1 = createAGraph(100);
    int AM[100][100];
    initAM(AM);
    FILE *file = fopen("graph", "r");
    addEdgeAM(file, AM);
    int inc_arr[100][2970];
    add_edge(file);
    searchIM(inc_arr, 20, 30, 2970);
    //get_edges_al(file, graph);
    //get_EL(file, edge_list);
    //search_edge_list(edge_list, 16, 70);
    searchAL(creatennodes(5), 13);
    searchAM(34, 5, AM);
    fclose(file);
    printf("pzdr GP\n");
    return 0;
}
