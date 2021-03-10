#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> grades1;
vector<vector<int>> grades2;
vector<vector<int>> grades3;




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

void nestedLoopJoin(vector<vector<int>> table1, vector<vector<int>> table2, int key) {
  printf("NESTEDLOOPJOIN: \n");
  printTable(table1);
  printTable(table2);
  printf("RESULT: \n");
  vector<vector<int>> result;
  for(int i=0; i < table1.size(); i++){
    for(int j=0; j < table2.size(); j++){
      if (table1[i][key] == table2[j][key]){
        vector<int> match;
        copy(table1[i].begin(), table1[i].end(), back_inserter(match));
        match.insert(match.end(), table2[j].begin(), table2[j].end());
        match.erase(match.begin() + key, match.begin() + (key +1));
        result.push_back(match);
      }
    }
  }
  printTable(result);
}
/*
vector<vector<int>> sortMergeJoin(vector<vector<int>> table1, vector<vector<int>> table2, int key) {
  vector<vector<int>> copyTable1;
  vector<vector<int>> copyTable2;
  copyTable1 = Sort(table1.begin(), table1.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
  return a[key] < b[key];
  });
  copyTable2 = Sort(table2.begin(), table2.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
  return a[key] < b[key];
  });
  //Todo: merge part of the sortMergeJoin
}*/

int main(){
  grades1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};
  grades2 = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}};
  grades3 = {
            {1, 1, 1},
            {8, 8, 8},
            {4, 4, 4}};

  nestedLoopJoin(grades1, grades2, 1);
  nestedLoopJoin(grades1, grades3, 0);
  return 1;
}
