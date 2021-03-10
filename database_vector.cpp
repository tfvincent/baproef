#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

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



vector<vector<int>> sortMergeJoin(vector<vector<int>>& table1, vector<vector<int>>& table2, int key) {
  printf("SORTMERGEJOIN: \n");
  vector<vector<int>> copyTable1;
  vector<vector<int>> copyTable2;
  vector<vector<int>> result;
  copy(table1.begin(), table1.end(), back_inserter(copyTable1));
  copy(table2.begin(), table2.end(), back_inserter(copyTable2));

  printf("BEFORE SORTING: \n");
  printTable(copyTable1);
  printTable(copyTable2);

  sort(copyTable1.begin(), copyTable1.end(), [](const vector<int>& a, const vector<int>& b) {
  return a[0] < b[0];
  });
  sort(copyTable2.begin(), copyTable2.end(), [](const vector<int>& a, const vector<int>& b) {
  return a[0] < b[0];
  });

  printf("AFTER SORTING: \n");
  printTable(copyTable1);
  printTable(copyTable2);

  int mark = 999;
  int table1idx = 0;
  int table2idx = 0;

  printf("RESULT: \n");
  do {

    if (mark == 999) {
      while(copyTable1[table1idx][key] < copyTable2[table2idx][key]) {
        table1idx += 1;
      }
      while(copyTable1[table1idx][key] > copyTable2[table2idx][key]) {
        table2idx += 1;
      }
      mark = table2idx;
    }
    if (copyTable1[table1idx][key] == copyTable2[table2idx][key]) {
      vector<int> match;
      copy(copyTable1[table1idx].begin(), copyTable1[table1idx].end(), back_inserter(match));
      match.insert(match.end(), copyTable2[table2idx].begin(), copyTable2[table2idx].end());
      match.erase(match.begin() + key, match.begin() + (key +1));
      printVector(match);
      result.push_back(match);
      table2idx += 1;
    } else {
      table2idx = mark;
      table1idx += 1;
      mark = 999;
    }
  }
  while (table1idx < copyTable1.size());

  printTable(result);

}

int main(){
  grades1 = {
            {22, 2},
            {28, 5},
            {31, 8},
            {31, 82},
            {44, 4},
            {58, 9}};
  grades2 = {
            {28, 103},
            {28, 104},
            {31, 101},
            {31, 102},
            {42, 142},
            {58, 107}};
  grades3 = {
            {1, 1, 1},
            {8, 8, 8},
            {4, 4, 4}};

  nestedLoopJoin(grades1, grades2, 0);
  sortMergeJoin(grades1, grades2, 0);
  return 1;
}
