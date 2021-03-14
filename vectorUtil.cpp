#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"

void addData(vector<vector<int>>& vec, vector<int>& input){
  vec.push_back(input);
}

void printVector(vector<int> const &input){

  printf("|");
  for (int i = 0; i < input.size(); i++) {
      cout << input[i] << '|';
  }
  printf("\n");
}

void printTable(vector<vector<int>> const &input){
  for (int i = 0; i < input.size(); i++){
    printVector(input[i]);
  }
  printf("\n");
}
