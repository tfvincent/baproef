//
// Created by tf_vincent on 5/20/21.
//

#include "benchmark.h"

Table generateRandomTable(int rows, vector<int> vars, int datasize){
    Table table;
    table.push_back(vars);

    for (int i = 1; i < rows; ++i) {
        Tuple tuple;
        for (int j = 0; j < vars.size(); ++j) {
            int value  = rand() % datasize;
            tuple.push_back(value);
        }
        table.push_back(tuple);
    }
    return table;
}

Table generateSkewTable(int rows, vector<int> vars){
    Table table;
    table.push_back(vars);

    for (int i = 0; i < rows; ++i) {
        Tuple tuple;
        for (int j = 0; j < vars.size(); ++j) {
            if (j == 1){
                int value1 = rand() % 100;
                tuple.push_back(value1);
            } else {
                int value = rand() % 10000;
                tuple.push_back(value);
            }
        }
        table.push_back(tuple);
    }
    return table;
}
