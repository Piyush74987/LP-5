#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;

void sequential_bubble_sort(int arr[],int size){
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }

    double start = omp_get_wtime();
    for(int i = 0; i < size - 1; i ++){
        for(int j = 0; j < size - i - 1; j++){
            if(array[j] > array[j+1]){
                swap(array[j],array[j+1]);
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort:\n";
    cout << endl;
    cout << "Time Required: " << end - start << endl;

}

void parallel_bubble_sort(int arr[],int size){
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    for(int k = 0; k < size;k ++){
        if(k % 2 == 0){
            #pragma omp parallel for
                for(int i = 1; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
        else{
            #pragma omp parallel for
                for(int i = 0; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
    }
    double end = omp_get_wtime();
    cout << "Parallel Bubble Sort:\n";
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}



int main(int argc, char const *argv[])
{
    int SIZE;
    int MAX = 1000000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int array[SIZE];
    for(int i = 0 ; i < SIZE; i ++){
        array[i] = rand() % MAX;
    }
    cout << endl;
    sequential_bubble_sort(array,SIZE);
    parallel_bubble_sort(array,SIZE);
    return 0;
}