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
#include "sortMergeJoin.h"

using namespace std;


QueryPlan findQueryPlan(Table relation1, Table relation2, Table relation3){
    QueryPlan queryPlan;
    queryPlan.push_back(relation1);
    queryPlan.push_back(relation2);
    queryPlan.push_back(relation3);
    sort(queryPlan.begin(), queryPlan.end(), [] (Table a, Table b){
    return a[0][0] < b[0][0];
    });
    return queryPlan;
}


Table join(Table relation1, Table relation2, Table relation3, Table (*func)(Table, Table)){
    Timer timer("Joining query");
    QueryPlan queryPlan = findQueryPlan(relation1, relation2, relation3);
    Table result = queryPlan[0];
    for (int i = 1; i < queryPlan.size(); ++i) {
        result = (*func)(result, queryPlan[i]);
    }
    unsigned long long duration = timer.Stop();
    return result;
}
