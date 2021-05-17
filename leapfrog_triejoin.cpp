//
// Created by tf_vincent on 5/17/21.
//

#include "vectorUtil.h"

struct node * addNodes(struct node * root, vector<int> data, int index){
    if (index < data.size()){
        if (find(root->children.begin(), root->children.end(), data[i]) == root->children.end()){
            struct node* child = newNode(data[i]);
            root->children.push_back(child);
            sort(root->children.begin(), root->children.end(), [](struct node * a, struct node * b){
                return a->data < b->data;
            });
            addNodes(newNode, data, i + 1);
        } else {
            auto it =  find(root->children.begin(), root->children.end(), data[i]);
            struct node * newNode = *it;
            addNodes(newNode, data, i + 1);
        }

    }
}

struct node * generateTrie(Table table, int c){
    int attributes = table[0].size();
    vector<int> uniqueNumbers;
    struct node* rootNode = new struct node();
    rootNode->data = c;
    for (int i = 1 ; i < table.size()){
        addNodes(rootNode, table[i], 0);
    }
}
