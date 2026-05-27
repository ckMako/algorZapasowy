#include "SORT/algorytmySortowania.h"

// void insertionSort(std::vector<int>& arr) {
//     int n = arr.size();
//     for (int i = 1; i < n; ++i) {
//         int key = arr[i];
//         int j = i - 1;

//         // przesuwamy elementy większe od key o jedno miejsce w prawo
//         while (j >= 0 && arr[j] > key) {
//             arr[j+1] = arr[j];
//             j--;
//         }
//         arr[j+1] = key;
//     }
// }