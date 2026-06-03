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
void insertionSort(std::vector<movie>& arr, std::vector<int>& indeksy);

