//
// Created by tf_vincent on 3/27/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <list>

#include "nestedLoopJoin.h"
#include "timer.h"
#include "vectorUtil.h"

using namespace std;


vector<vector<vector<int>>> findQueryPlan(vector<vector<int>> relation1, vector<vector<int>> relation2, vector<vector<int>> relation3){
    vector<vector<vector<int>>> queryPlan;
    queryPlan.push_back(relation1);
    queryPlan.push_back(relation2);
    queryPlan.push_back(relation3);
    sort(queryPlan.begin(), queryPlan.end(), [] (vector<vector<int>> a, vector<vector<int>> b){
    return a[0] < b[0];
    });
    return queryPlan;
}


unsigned long long join(vector<vector<int>> relation1, vector<vector<int>> relation2, vector<vector<int>> relation3){
    Timer timer("Joining query");
    vector<vector<vector<int>>>queryPlan = findQueryPlan(relation1, relation2, relation3);
    vector<vector<int>> result = queryPlan[0];
    for (int i = 1; i < queryPlan.size(); ++i) {
        result = nestedLoopJoin(result, queryPlan[i]);
    }
    unsigned long long duration = timer.Stop();
    printTable(result);
    return duration;
}
