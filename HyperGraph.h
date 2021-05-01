//
// Created by tf_vincent on 4/30/21.
//

#ifndef BAPROEF_HYPERGRAPH_H
#define BAPROEF_HYPERGRAPH_H

#include "vectorUtil.h"

class HyperGraph {

public:

    vector<Table> vertices;
    vector<Tuple> edgeSets;

    int size();

    bool contains(int, Tuple);
};


#endif //BAPROEF_HYPERGRAPH_H
