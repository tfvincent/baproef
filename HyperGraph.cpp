//
// Created by tf_vincent on 4/30/21.
//

#include "HyperGraph.h"
#include "vectorUtil.h"

int HyperGraph::size() {
    return vertices.size();
}

bool HyperGraph::contains(int var, Tuple edgeSet) {
    return find(edgeSet.begin(), edgeSet.end(), var) != edgeSet.end();
}