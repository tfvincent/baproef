#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"

using namespace std;

void printVector(Tuple const &input){

  printf("|");
  for (int i = 0; i < input.size(); i++) {
      cout << input[i] << '|';
  }
  printf("\n");
}

Pair findKeys(Table& table1, Table& table2){
    Pair result;
    for(int s = 0; s < table1[0].size(); s++) {
        for (int p = 0; p < table2[0].size(); p++) {
            if (table1[0][s] == table2[0][p]) {
                result.first = s;
                result.second = p;
            }
        }
    }
    return result;
}
void printTable(Table const &input){
  for (int i = 0; i < input.size(); i++){
    printVector(input[i]);
  }
  printf("\n");
}
