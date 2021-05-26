#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "genericJoin.h"

Table resultGenericJoin;

HyperGraph * generateHyperGraph(vector<Table>& tables) {
    auto * hyperGraph = new HyperGraph();
    Tuple attributes;
    Table edgeSets;
    for (auto table :tables) {
        Tuple edgeSet;
        for (int & i : table[0]) {
            if (find(attributes.begin(), attributes.end(), i) == attributes.end()) {
                attributes.push_back(i);
            }
            edgeSet.push_back(i);
        }
        edgeSets.push_back(edgeSet);
    }
    hyperGraph->vertices = attributes;
    hyperGraph->edgeSets = edgeSets;

    return hyperGraph;
}

Table genericJoin(HyperGraph * graph,  vector<Table>& tables, int i) {
    vector<Table> rJoin, rOther;

    if (i <= graph->size()) {
        for(int j = 0; j < tables.size(); j++){
            if (graph->contains(i, graph->edgeSets[j])){
                rJoin.push_back(tables[j]);
            } else {
                rOther.push_back(tables[j]);
	        }
	    }
        vector<int> rIntersect = project(i, rJoin[0]);
        vector<int> rIntersection;
        for(int j = 1; j < rJoin.size(); j++){
            vector<int> second = project(i, rJoin[j]);
            set_intersection(rIntersect.begin(), rIntersect.end(), second.begin(), second.end(),  back_inserter(rIntersection));
            rIntersection.erase( unique( rIntersection.begin(), rIntersection.end() ), rIntersection.end() );
        }

        for(int x: rIntersection){
            vector<Table> rNext;
           for(auto & j : rJoin){
               rNext.push_back(select(i, j, x));
           }
           vector<Table> recursionTables = rNext;
           for (const auto& table : rOther){
               recursionTables.push_back(table);
           }
           HyperGraph * hyperGraph = generateHyperGraph(recursionTables);
           genericJoin(hyperGraph, recursionTables, i + 1);
        }

    } else {
        Tuple tmp;
        for (auto x: tables){
            copy (x[1].begin(), x[1].end(), back_inserter(tmp));
        }
        resultGenericJoin.push_back(tmp);
    }
    return resultGenericJoin;
}    
