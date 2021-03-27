#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "nestedLoopJoin.h"
#include "timer.h"

using namespace std;
vector<vector<int>> nestedLoopJoin(vector<vector<int>> table1, vector<vector<int>> table2) {
    pair<int, int> keys = findKeys(table1, table2);
    vector<vector<int>> result;
    result.reserve(50);
    Timer timer("Nested_loop_join");
    for(int i=0; i < table1.size(); i++){
        for(int j=0; j < table2.size(); j++){
            if (table1[i][keys.first] == table2[j][keys.second]){
                vector<int> match;
                match.reserve(5);
                copy(table1[i].begin(), table1[i].end(), back_inserter(match));
                match.insert(match.end(), table2[j].begin(), table2[j].end());
                match.erase(match.begin() + keys.first, match.begin() + (keys.first +1));
                result.push_back(match);
            }
        }
    }
    //printTable(result);
    //unsigned long long duration = timer.Stop();
    return result;
}
