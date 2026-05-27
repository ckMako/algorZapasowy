#pragma once

#include "movie.h"

/**
 * @param vector pointer na wektor do posortownaia
 * @return sorted
 */
template<class T>
void bubbleSort(std::vector<T>& arr) {
    std::cout<<"BubbleSort"<<std::endl;
    int rozmr = arr.size();
    for (int i = 0; i < rozmr-1; ++i) {
        for (int j = 0; j < rozmr-i-1; ++j) {
            if (*arr[j] > *arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}


/**
 * @param vector pointer na vect
 * @return sorted
 */
template<class T>
void insertionSort(std::vector<T>& arr) {
    std::cout << "InsertionSort" << std::endl;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];          // T zamiast int
        int j = i - 1;
        while (j >= 0 && *arr[j] > *key) {  // dereferencja
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}


