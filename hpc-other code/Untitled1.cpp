#include<iostream>
#include<omp.h>
#include<vector>
#include<climits>
#include <cstdlib>

using namespace std;

void minimum(vector<int> array){
    int min = INT_MAX;
    double start = omp_get_wtime();
    // Sequential loop for minimum
    for(vector<int>::iterator i = array.begin(); i != array.end(); ++i){
        if(*i < min){
            min = *i;
        } 
    }
    double end = omp_get_wtime();
    cout << "Minimum Element: " << min << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl; 
    
    int min_ele = INT_MAX;
    start = omp_get_wtime();
    // Parallel loop for minimum with reduction
    #pragma omp parallel for reduction(min: min_ele)
    for(int i = 0; i < array.size(); ++i){
        if(array[i] < min_ele){
            min_ele = array[i];
        } 
    }
    end = omp_get_wtime();
    cout << "Minimum Element(Parallel Reduction): " << min_ele << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl;
}

void maximum(vector<int> array){
    int max = INT_MIN;
    double start = omp_get_wtime();
    // Sequential loop for maximum
    for(vector<int>::iterator i = array.begin(); i != array.end(); ++i){
        if(*i > max){
            max = *i;
        } 
    }
    double end = omp_get_wtime();
    cout << "Maximum Element: " << max << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl; 
    
    int max_ele = INT_MIN;
    start = omp_get_wtime();
    // Parallel loop for maximum with reduction
    #pragma omp parallel for reduction(max: max_ele)
    for(int i = 0; i < array.size(); ++i){
        if(array[i] > max_ele){
            max_ele = array[i];
        } 
    }
    end = omp_get_wtime();
    cout << "Maximum Element(Parallel Reduction): " << max_ele << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl;
}

void sum(vector<int> array){
    int sum = 0;
    double start = omp_get_wtime();
    // Sequential loop for summation
    for(vector<int>::iterator i = array.begin(); i != array.end(); ++i){
        sum += *i; 
    }
    double end = omp_get_wtime();
    cout << "Summation: " << sum << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl; 
    
    sum = 0;
    start = omp_get_wtime();
    // Parallel loop for summation with reduction
    #pragma omp parallel for reduction(+: sum)
    for(int i = 0; i < array.size(); ++i){
        sum += array[i]; 
    }
    end = omp_get_wtime();
    cout << "Summation(Parallel Reduction): " << sum << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl;
}

void average(vector<int> array){
    float avg = 0;
    double start = omp_get_wtime();
    // Sequential loop for average calculation
    for(vector<int>::iterator i = array.begin(); i != array.end(); ++i){
        avg += *i; 
    }
    double end = omp_get_wtime();
    cout << "Average: " << avg / array.size() << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl; 
    
    avg = 0;
    start = omp_get_wtime();
    // Parallel loop for average calculation with reduction
    #pragma omp parallel for reduction(+: avg)
    for(int i = 0; i < array.size(); ++i){
        avg += array[i]; 
    }
    end = omp_get_wtime();
    cout << "Average(Parallel Reduction): " << avg / array.size() << endl;
    cout << "Time Taken: " << (end-start) << " seconds" << endl;
}

int main(){
    cout << "Enter number of elements in array: ";
    int N;
    int MAX = 1000;
    cin >> N;
    vector<int> array;
    
    // Generate random elements for the array
    for(int i = 0; i < N; i++){
        array.push_back(rand() % MAX);
    }

    minimum(array);
    maximum(array);
    sum(array);
    average(array);

    return 0;
}

