#include "SORT/algorytmySortowania.h"

void insertionSort(std::vector<movie>& arr, std::vector<int>& indeksy) {
    int n = indeksy.size();
    for (int i = 1; i < n; i++) {
        int key = indeksy[i];
        int j = i - 1;
        while (j >= 0 && arr[indeksy[j]] > arr[key]) {
            indeksy[j+1] = indeksy[j];
            j--;
        }
        indeksy[j+1] = key;
    }
}