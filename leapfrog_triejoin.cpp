//
// Created by tf_vincent on 5/17/21.
//

#include "vectorUtil.h"
#include "TrieIterator.h"
#include "leapfrog_join.h"
#include "timer.h"

int depth = 0;
Table result;

struct node * addNodes(struct node * root, vector<int> data, int index, Tuple vars){
    if (index < data.size()){
        if (find_if(root->children.begin(), root->children.end(), [data, index] (struct node * a) -> bool {
            return a->data == data[index];
        }) == root->children.end()){
            struct node* child = newNode(data[index], root, vars[index], index);
            root->children.push_back(child);
            sort(root->children.begin(), root->children.end(), [](struct node * a, struct node * b){
                return a->data < b->data;
            });
            addNodes(child, data, index + 1, vars);
        } else {
            auto it =  find_if(root->children.begin(), root->children.end(), [data, index] (struct node * a) -> bool {
                return a->data == data[index];
            });
            struct node * newNode = *it;
            addNodes(newNode, data, index + 1, vars);
        }

    } else {
        return root;
    }
}

struct node * generateTrie(Table table, int c){
    vector<int> uniqueNumbers;
    struct node * rootNode = newNode(c, NULL, NULL, 0);
    rootNode->data = c;
    rootNode->vars = table[0];
    for (int i = 1 ; i < table.size(); i++){
        addNodes(rootNode, table[i], 0, table[0]);
    }
    return rootNode;
}

vector<vector<TrieIterator*>> getTrieTable(vector<TrieIterator*> tries, vector<int> varOrder){
    vector<vector<TrieIterator*>> result;
    for (int i = 0; i < varOrder.size(); ++i) {
        vector<TrieIterator*> tmp;
        for (int j = 0; j < tries.size(); ++j) {
            if (find(tries[j]->current->vars.begin(), tries[j]->current->vars.end(), varOrder[i]) != tries[j]->current->vars.end()){
                tmp.push_back(tries[j]);
            }
        }
        result.push_back(tmp);
    }
    return result;
}

void leapfrogTriejoinOpen(vector<TrieIterator*> &iterVec){
    depth++;
    for (auto x : iterVec) {
        x->open();
    }
    leapfrog_init(iterVec);
}

void leapfrogTriejoinUp(vector<TrieIterator*> &iterVec){
    --depth;
    for(auto x: iterVec){
        x->up();
    }
}

Tuple getPath(vector<TrieIterator*> &iterVec){
    Table tmpTable;
    for (int i = 0; i < iterVec.size(); ++i) {
        vector<int> tmp;
        struct node * curr = iterVec[i]->current;
        while (curr->var != NULL) {
            tmp.push_back(curr->data);
            curr = curr->parent;
        }
        tmpTable.push_back(tmp);
    }
    Tuple result;
    for (int i = 0; i < tmpTable.size(); ++i) {
        result.insert(result.end(), tmpTable[i].begin(), tmpTable[i].end());
    }
    return result;
}

void leapfrogTriejoin(vector<vector<TrieIterator*>> &vars, vector<TrieIterator*> &itervec) {
    Table result;
    if (depth >= 0) {
        if (depth == 0){
            leapfrogTriejoinOpen(vars[depth]);
            leapfrogTriejoin(vars, itervec);
        }
        if (depth < vars.size() && (!vars[depth-1][0]->atEnd() && vars[depth-1][1]->atEnd())) {
            leapfrogTriejoinOpen(vars[depth]);
            leapfrogTriejoin(vars, itervec);
            while (leapfrog_next(vars[depth - 1])) {
                leapfrogTriejoin(vars, itervec);
            }
            leapfrogTriejoinUp(vars[depth - 1]);

        }
        if (depth == vars.size()) {
            Tuple tmp = getPath(itervec);
            result.push_back(tmp);
        }
    }
    return;
}