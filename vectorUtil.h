#ifndef VECTORUTIL_H_
#define VECTORUTIL_H_

#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "map.h"
#include "btree.h"

using namespace std;
typedef vector<int> Tuple;
typedef vector<vector<int>> Table;
typedef vector<vector<vector<int>>> QueryPlan;
typedef pair<int, int> Pair;
typedef btree::map<int, Tuple*> IndexMap;


class Index {
public:
    Index(Table * table);
    IndexMap index;
    Table * table;
};

struct node  {

public:
    int data;
    int var;
    int index;
    struct node * parent;
    vector<int> vars;
    vector<struct node *> children;
};

struct node* newNode(int, struct node *, int, int);

void addData(Table&, Tuple&);

Pair findKeys(Table&, Table&);

vector<int> project(int, Table);

int findIndex(int, Table);

Table select(int, Table, int);

Table product(const vector<Table>&);

Index * makeIndex(Table* , int);

void printVector(Tuple const &);

void printTable(Table const &);

void printTrie(struct node *);


#endif
