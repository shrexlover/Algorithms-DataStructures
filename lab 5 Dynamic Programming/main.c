#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapSackBF(int W, int wt[], int val[], int n)
{
    if (n == 0 || W == 0)
        return 0;
    if (wt[n - 1] > W)
        return knapSackBF(W, wt, val, n - 1);

    else
        return max(
                val[n - 1]
                + knapSackBF(W - wt[n - 1],
                           wt, val, n - 1),
                knapSackBF(W, wt, val, n - 1));
}

int knapSackDP(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1]
                              + K[i - 1][w - wt[i - 1]],
                              K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}
void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap2 (double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

int partition(double *arr, int *arr2, int *arr3, int start, int end){
    double pivot = arr[(start+end)/2];
    swap2(&arr[end], &arr[(start+end)/2]);
    swap(&arr2[end], &arr2[(start+end)/2]);
    swap(&arr3[end], &arr3[(start+end)/2]);
    int i=(start-1);
    for(int j=start; j<= end-1; j++){
        if(arr[j] > pivot){
            i++;
            swap2(&arr[i], &arr[j]);
            swap(&arr2[i], &arr2[j]);
            swap(&arr3[i], &arr3[j]);
        }
    }
    swap2(&arr[i+1], &arr[end]);
    swap(&arr2[i+1], &arr2[end]);
    swap(&arr3[i+1], &arr3[end]);
    return i+1;
}

void quickSort(double *arr, int *arr2, int *arr3, int start, int end){

    while(start < end) {
        int mid = partition(arr, arr2, arr3, start, end);
        if (mid - start <= end-(mid+1)){
            quickSort(arr, arr2, arr3, start, mid);
            start = mid+1;
        }
        else{
            quickSort(arr, arr2, arr3, mid+1, end);
            end = mid;
        }
    }
}


double greedy_knapsack_low (int number_of_items, int max_weight, int values[], int weights[]){
    double profit[number_of_items];
    for (int i=0;i<number_of_items;i++)
        profit[i] =  (double)values[i] / weights[i];

    quickSort(profit, values, weights, 0, number_of_items-1);

    int c_weight = 0;
    double c_value = 0;
    int i=0;
    while ((c_weight += weights[i]) <= max_weight){

        c_value += values[i];
        i++;
    }
    return c_value;
}

double greedy_knapsack_up (int number_of_items, int max_weight, int values[], int weights[]){
    double profit[number_of_items];
    for (int i=0;i<number_of_items;i++)
        profit[i] =  (double)values[i] / weights[i];

    quickSort(profit, values, weights, 0, number_of_items-1);

    int c_weight = 0;
    double c_value = 0;
    int i=0;
    while ((c_weight += weights[i]) <= max_weight){

        c_value += values[i];
        i++;
    }
    c_weight -= weights[i];
    c_value +=(double) (max_weight - c_weight) / weights[i] * values[i];
    return c_value;
}

int main()
{
    int num = 100;
    int val[100];
    int wt[100];
    int W = 50;
    char* line;
    FILE *file = fopen("graph", "r");
    while(fgets(line, 5, file)){
        char* a;
        char* b;
        scanf("%s %s", atoi(a), atoi(b));
        val[atoi(a)] = atoi(a);
        wt[(atoi(a))] = atoi(b);
    }
    int n = sizeof(val) / sizeof(val[0]);
    greedy_knapsack_low(num, W, val, wt);
    greedy_knapsack_up(num, W, val, wt);
    printf("%d", knapSackDP(W, wt, val, n));
    printf("%d", knapSackBF(W, wt, val, n));
    return 0;
}

