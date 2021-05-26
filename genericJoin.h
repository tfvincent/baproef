#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "HyperGraph.h"

HyperGraph * generateHyperGraph(vector<Table>&);

Table genericJoin(HyperGraph *, vector<Table >&, int);
