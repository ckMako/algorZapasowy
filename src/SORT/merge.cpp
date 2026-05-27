#include "SORT/merge.h"

void merge(std::vector<movie>& movies, std::vector<int>& indx, 
           int left, int mid, int right) {
    
    // tymczasowe wektory
    std::vector<int> L(indx.begin() + left,  indx.begin() + mid + 1);
    std::vector<int> R(indx.begin() + mid + 1, indx.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < L.size() && j < R.size()) {
        // porównuj przez indeks do movies
        if (movies[L[i]].getAverageRating() <= movies[R[j]].getAverageRating())
            indx[k++] = L[i++];
        else
            indx[k++] = R[j++];
    }

    while (i < L.size()) indx[k++] = L[i++];
    while (j < R.size()) indx[k++] = R[j++];
}

void mergeSort(std::vector<movie>& movies, std::vector<int>& indx,
               int left, int right) {
    if (left >= right) return;  // warunek stopu

    int mid = left + (right - left) / 2;

    mergeSort(movies, indx, left, mid);       // lewa połowa
    mergeSort(movies, indx, mid + 1, right);  // prawa połowa
    merge(movies, indx, left, mid, right);    // scal
}