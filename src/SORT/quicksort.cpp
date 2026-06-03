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

/**
 * @brief przed optym, napotyka duplikaty
 */
void quickSort(std::vector<movie>& movies, std::vector<int>& indx,
               int left, int right) {
    if (left >= right) return;
    int pivotIdx = partition(movies, indx, left, right);
    quickSort(movies, indx, left, pivotIdx - 1);
    quickSort(movies, indx, pivotIdx + 1, right);
}

/**
 * @brief mniej duplikatow
 */
void quickSort3(std::vector<movie>& movies, std::vector<int>& indx,
                int left, int right) {
    if (left >= right) return;
    float pivot = movies[indx[left + (right-left)/2]].getAverageRating();
    int lt = left, gt = right, i = left;
    while (i <= gt) {
        float cur = movies[indx[i]].getAverageRating();
        if (cur < pivot)
            std::swap(indx[lt++], indx[i++]);
        else if (cur > pivot)
            std::swap(indx[i], indx[gt--]);
        else
            i++;
    }
    // [left..lt-1] < pivot, [lt..gt] == pivot, [gt+1..right] > pivot
    quickSort3(movies, indx, left, lt - 1);
    quickSort3(movies, indx, gt + 1, right);
}

void quickSort(std::vector<movie>& movies, std::vector<int>& indx) {
    quickSort3(movies, indx, 0, indx.size() - 1);
}