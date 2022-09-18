#include <stdio.h>
#include <stdlib.h>
void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void fillingArray (int t[],int x,int range)
{
    for (int i=0;i<x;i++)
        t[i]=rand()%range;
}
void filling_a_shape (int t[], int x)
{
    for (int i = 0; i < x/2; i++)
    {
        t[i] = 2*i + 1;
    }
    for (int i = x-1; i >= (x/2); i--)
    {
        t[i] = 2*(x-1 - i);
    }
}
void filling_v_shape (int t[], int x)
{
    for (int i = 0; i < (x/2); i++)
    {
        t[i] = (x-2*i - 1);
    }
    for (int i = x-1; i >= (x/2); i--)
    {
        t[i] = (t[x-i] + 1);
    }
    t[x/2] = 0;
}
void filling_constant (int t[], int x)
{
    for (int i=0;i<x;i++)
        t[i] = 0;
}
void filling_inc1 (int t[], int x)
{
    for (int i=0;i<x;i++)
        t[i] = i;
}
void filling_dec1 (int t[], int x)
{
    for (int i=0;i<x;i++)
        t[i] = x-i;
}
void swapbubble(int l[], int index, int pos)
{
    int temp = l[pos];
    l[pos] = l[index];
    l[index] = temp;
}
void bubble_sort(int l[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (l[j] > l[j + 1])
            {
                swapbubble(l, j+1, j);
            }
        }
    }
}
int partition(int *arr, int start, int end){
    int pivot = arr[(start+end)/2];
    swap(&arr[end], &arr[(start+end)/2]);
    int i=(start-1);
    for(int j=start; j<= end-1; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[end]);
    return i+1;
}

void quickSort(int *arr, int start, int end){
    while(start < end) {
        int mid = partition(arr, start, end);
        if (mid - start <= end-(mid+1)){
            quickSort(arr, start, mid);
            start = mid+1;
        }
        else{
            quickSort(arr, mid+1, end);
            end = mid;
        }
    }
}

void countingSort(int array[], int size) {
    int output[10];

    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }
    int count[10];

    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }
}


void merge(int arr[], int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

void shellSort(int array[], int n) {

    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}



int main() {

    int size = 170000;
    int range = 10000;
    int t[size];

    fillingArray(t, size, range);
    filling_inc1 (t,size);
    filling_dec1 (t,size);
    filling_a_shape(t, size);
    filling_v_shape(t, size);
    filling_constant(t, size);


     for (int i=0; i<=230000; i+=10000)
     {
         size = i;
         mergeSort(t, 0, size-1);
         heapSort(t,size);
         quickSort(t,0,size-1);
         shellSort(t, size);
         countingSort(t, size);
         bubble_sort(t, size);

     }
     return 0;

}
