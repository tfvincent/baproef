//
// Created by tf_vincent on 3/27/21.
//

#ifndef BAPROEF_JOIN_H
#define BAPROEF_JOIN_H

#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <list>

QueryPlan findQueryPlan(Table, Table, Table);

unsigned long long join(Table, Table, Table);


#endif //BAPROEF_JOIN_H
