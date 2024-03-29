//
// Created by tf_vincent on 5/20/21.
//

#include "benchmark.h"

Table * generateRandomTable(int rows, vector<int> vars, int datasize){
    Table * table = new Table();
    table->push_back(vars);
    srand(time (0));
    for (int i = 1; i < rows; ++i) {
        Tuple tuple;
        for (int j = 0; j < vars.size(); ++j) {
            int value  = rand() % datasize;
            tuple.push_back(value);
        }
        table->push_back(tuple);
    }
    return table;
}

vector<Table*> generateSkewTable(int rows, vector<vector<int>> vars){
    vector<Table*> tables;
    int desiredVal = 1;

    for (int i = 0; i < vars.size(); ++i) {
        Table * table = new Table();
        table->push_back(vars[i]);
        int index = 999;
        if (find(vars[i].begin(), vars[i].end(), desiredVal) != vars[i].end()) {

            for (int j = 0; j < vars[i].size(); ++j) {
                if (vars[i][j] == desiredVal) {
                    index = j;
                }
            }

            for (int p = 0; p < rows; ++p) {
                Tuple tuple;
                for (int j = 0; j < vars[i].size(); ++j) {
                    if (j == index) {
                        tuple.push_back(7);
                    } else {
                        tuple.push_back(p);
                    }
                }
                table->push_back(tuple);
            }
            tables.push_back(table);
        } else {
            for (int p = 0; p < rows/2; ++p) {
                Tuple tuple;
                for (int j = 0; j < vars[i].size(); ++j) {
                    tuple.push_back(p);
                }
                table->push_back(tuple);
                Tuple tuple2;

                for (int j = 0; j < vars[i].size(); ++j) {
                    tuple2.push_back(p);
                }
                table->push_back(tuple2);
            }
            tables.push_back(table);
        }
    }
    return tables;
}

vector<Table*> generateSkewTableUnsorted(int rows, vector<vector<int>> vars){

     vector<Table*> unSortedTables = generateSkewTable(rows, vars);

     for(auto x: unSortedTables){
         random_shuffle(x->begin(), x->end());
     }

     return unSortedTables;
}

vector<Table*> generateNoSolutionSkew(int rows, vector<vector<int>> vars){
    vector<Table*> tables;
    Tuple table0 = {1,2};
    Tuple table1 = {2,3};
    Tuple table2 = {1,3};

    for (int i = 0; i < vars.size(); ++i) {
        Table * table = new Table ();
        table->push_back(vars[i]);
        for (int j = 0; j < rows; ++j) {
            Tuple tuple;
            if (vars[i] == table0){
                tuple.push_back(7);
                tuple.push_back(j);
            } else if (vars[i] == table1){
                tuple.push_back(j);
                tuple.push_back(j);
            } else {
                tuple.push_back(7);
                tuple.push_back(j+rows);
            }
            table->push_back(tuple);
        }
        tables.push_back(table);
    }
    return tables;
}