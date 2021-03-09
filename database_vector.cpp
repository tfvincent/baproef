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

vector<vector<int>> nestedLoopJoin(vector<vector<int>> table1, vector<vector<int>> table2, int key) {
  vector<vector<int>> result;
  for(int i=0; i < table1.size(); i++){
    for(int j=0; i < table2.size(); j++){
      if (table1[i][key] == table2[j][key])
        vector<int> match;
        copy(table1[i].begin(), table1[i].end(), back_inserter(match));
        result.push_back(match.insert(match.end(), table2[j].begin(), table2[j].end()));
    }
  }
  //Todo: delete matching column from the result (helper function?)
  return result;
}

vector<vector<int> sortMergeJoin(vector<vector<int>> table1, vector<vector<int>> table2, int key) {
  vector<vector<int>> copyTable1;
  vector<vector<int>> copyTable2;
  copyTable1 = Sort(table1.begin(), table1.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
  return a[key] < b[key];
  });
  copyTable2 = Sort(table2.begin(), table2.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
  return a[key] < b[key];
  });
  //Todo: merge part of the sortMergeJoin
}

int main(){
  printf("Work is Worship");
  grades1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}}
  grades2 = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}}
  grades3 = {
            {1, 1, 1},
            {8, 8, 8},
            {4, 4, 4}}  
  printf(nestedLoopJoin(grades1, grades2, 2));
  printf(nestedloopJoin(grades1, grades3, 1))
}
