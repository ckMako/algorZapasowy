#pragma once
#include "movie.h"
#include <vector>

int partition(std::vector<movie>& movies, std::vector<int>& indx,
              int left, int right);

void quickSort(std::vector<movie>& movies, std::vector<int>& indx,
               int left, int right);

void quickSort(std::vector<movie>& movies, std::vector<int>& indx);