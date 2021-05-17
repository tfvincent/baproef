#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "map.h"
using namespace std;

//https://www.softwaretestinghelp.com/trees-in-cpp/#:~:text=A%20tree%20is%20a%20collection,but%20only%20one%20parent%20node.
//declaration for new tree node
struct node  {
    int data;
    vector<struct node *> children;
};

//allocates new node
struct node* newNode(int data) {
    // declare and allocate new node
    struct node* node = new struct node();

    node->data = data;    // Assign data to this node

    return(node);
}


Index::Index(Table * table) {
    this->table = table;
    this->index = btree::map<int, vector<int> *> ();
}

void printVector(Tuple const &input){

    printf("|");
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << '|';
    }
    printf("\n");
}

Pair findKeys(Table& table1, Table& table2){
    Pair result;
    for(int s = 0; s < table1[0].size(); s++) {
        for (int p = 0; p < table2[0].size(); p++) {
            if (table1[0][s] == table2[0][p]) {
                result.first = s;
                result.second = p;
            }
        }
    }
    return result;
}

int findIndex(int var, Table table){
    for(int i = 0; i < table.size(); i++){
        // FIXED: "=" is not the same as "=="!
        if(table[0][i] == var){
            return i;
        }
    }
}

vector<int> project(int var, Table table){
    vector<int> result;
    int index = findIndex(var, table);
    for(int i = 1; i < table.size(); i++){
        result.push_back(table[i][index]);
    }
    return result;
}

Table select(int var, Table table, int value){
    Table result;
    result.push_back(table[0]);
    int index = findIndex(var, table);
    for(int i = 0; i < table.size(); i++){
        if(table[i][index] == value){
            result.push_back(table[i]);
        }
    }
    return result;
}

//https://rosettacode.org/wiki/Cartesian_product_of_two_or_more_lists#C.2B.2B
Table product(const vector<Table>& lists) {
    Table result;
    if (find_if(begin(lists), end(lists),
                [](auto e) -> bool { return e.size() == 0; }) != end(lists)) {
        return result;
    }
    for (auto& e : lists[0]) {
        result.push_back({ e });
    }
    for (size_t i = 1; i < lists.size(); ++i) {
        vector<vector<int>> temp;
        for (auto& e : result) {
            for (auto f : lists[i]) {
                for (auto g: f) {
                    auto e_tmp = e;
                    e_tmp.push_back(g);
                    temp.push_back(e_tmp);
                }
            }
        }
        result = temp;
    }
    return result;
}

Index * makeIndex(Table* table, int variable){
    int column = findIndex(variable,  *table);
    Index * indexTable = new Index(table);
    for (int i = 0; i < table->size(); ++i) {
        auto key = table->operator[](i)[column];
        if (indexTable->index.count(key) == 1) {
            auto keyVector = indexTable->index[key];
            keyVector->push_back(i);
        } else {
            auto newVector = new vector<int>();
            indexTable->index[key] = newVector;
            newVector->push_back(i);
        }
    }
    return indexTable;
}

void printTable(Table const &input){
    for (int i = 0; i < input.size(); i++){
        printVector(input[i]);
    }
    printf("\n");
}
