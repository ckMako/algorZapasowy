#pragma once
#include "movieReader.h"

void merge(std::vector<movie>& movies, std::vector<int>& indx,
           int left, int mid, int right);

void mergeSort(std::vector<movie>& movies, std::vector<int>& indx,
               int left, int right);