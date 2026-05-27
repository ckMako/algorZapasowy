#include "SORT/quicksort.h"

int partition(std::vector<movie>& movies, std::vector<int>& indx,
              int left, int right) {

    float pivot = movies[indx[right]].getAverageRating();
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (movies[indx[j]].getAverageRating() < pivot) {
            ++i;
            std::swap(indx[i], indx[j]);
        }
    }
    std::swap(indx[i + 1], indx[right]);
    return i + 1;
}

void quickSort(std::vector<movie>& movies, std::vector<int>& indx,
               int left, int right) {
    if (left >= right) return;

    int pivotIdx = partition(movies, indx, left, right);
    quickSort(movies, indx, left, pivotIdx - 1);
    quickSort(movies, indx, pivotIdx + 1, right);
}

void quickSort(std::vector<movie>& movies, std::vector<int>& indx) {
    quickSort(movies, indx, 0, indx.size() - 1);
}