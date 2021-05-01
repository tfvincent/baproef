    #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "genericJoin.h"
#include "timer.h"

//still to be implemented: HyperGraph and Debugging

Table genericJoin(HyperGraph graph, vector<Table> tables, int i) {
    vector<Table> rJoin, rOther, rNext;
    if (i <= graph.size()) {
        for(int j = 0; j < tables.size(); j++){
	    if (graph.contains(i, graph.edgeSets[j])){
	        rJoin.push_back(tables[j]);
	    } else {
		rOther.push_back(tables[j]);
	    }
	}
	vector<int> rIntersect = project(i, rJoin[0]);
	for(int j = 1; j < rJoin.size(); j++){
	    vector<int> second = project(i, rJoin[j]);
	    set_intersection(rIntersect.begin(), rIntersect.end(), second.begin(), second.end(), rIntersect.begin());
	 
	}
       for(int x: rIntersect){
           for(int j = 0; j < rJoin.size(); j++){
	       rNext.push_back(select(i, rJoin[j], x));
           }
           genericJoin(graph, rNext, i + 1);
       }
    } else {
        product(rNext);
    }
}    
