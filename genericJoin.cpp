#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "genericJoin.h"

HyperGraph * generateHyperGraph(vector<Table>& tables) {
    auto * hyperGraph = new HyperGraph();
    Tuple attributes;
    Table edgeSets;
    for (auto table :tables) {
        Tuple edgeSet;
        for (int i = 0; i < table[0].size() ; ++i) {
            if (find(attributes.begin(), attributes.end(), table[0][i]) == attributes.end()) {
                attributes.push_back(table[0][i]);
            }
            edgeSet.push_back(table[0][i]);
        }
        edgeSets.push_back(edgeSet);
    }
    hyperGraph->vertices = attributes;
    hyperGraph->edgeSets = edgeSets;

    return hyperGraph;
}

Table genericJoin(HyperGraph * graph,  vector<Table>& tables, int i) {
    vector<Table> rJoin, rOther, rNext;

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
            vector<int> tmp;
            set_intersection(rIntersect.begin(), rIntersect.end(), second.begin(), second.end(),  inserter(rIntersection, rIntersection.end()));
        }
        for(int x: rIntersection){
           for(auto & j : rJoin){
               rNext.push_back(select(i, j, x));
           }
           vector<Table> recursionTables = rNext;
           for (auto table : rOther){
               recursionTables.push_back(table);
           }
           HyperGraph * hyperGraph = generateHyperGraph(recursionTables);
           return genericJoin(hyperGraph, recursionTables, i + 1);
       }


    } else {
        Table result;

        for (int i = 0 ; i < tables[0].size(); i++){
            Tuple tmp;
            for (auto x: tables){
                copy (x[i].begin(), x[i].end(), back_inserter(tmp));
            }
            result.push_back(tmp);
        }
        return result;
    }
}    
