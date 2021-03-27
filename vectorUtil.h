#ifndef VECTORUTIL_H_
#define VECTORUTIL_H_

#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void addData(vector<vector<int>>&, vector<int>&);

pair<int,int> findKeys(vector<vector<int>>&, vector<vector<int>>&);

void printVector(vector<int> const &);

void printTable(vector<vector<int>>const &);

#endif
