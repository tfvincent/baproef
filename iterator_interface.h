//
// Created by tf_vincent on 4/30/21.
//

#ifndef BAPROEF_ITERATOR_INTERFACE_H
#define BAPROEF_ITERATOR_INTERFACE_H

#include "vectorUtil.h"

void seek(int, IndexMap::iterator*, IndexMap*);
bool isNotAtEnd(IndexMap::iterator&, IndexMap);

#endif //BAPROEF_ITERATOR_INTERFACE_H
