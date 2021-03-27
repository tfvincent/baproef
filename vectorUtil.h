#ifndef VECTORUTIL_H_
#define VECTORUTIL_H_

#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> Tuple;
typedef vector<vector<int>> Table;
typedef vector<vector<vector<int>>> QueryPlan;
typedef pair<int, int> Pair;

void addData(Table&, Tuple&);

Pair findKeys(Table&, Table&);

void printVector(Tuple const &);

void printTable(Table const &);

#endif
