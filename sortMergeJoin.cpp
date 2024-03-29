#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "sortMergeJoin.h"
#include "timer.h"

Table sortMergeJoin(Table table1, Table table2) {

  Table copyTable1;
  Table copyTable2;
  Table presult;

  copy(table1.begin(), table1.end(), back_inserter(copyTable1));
  copy(table2.begin(), table2.end(), back_inserter(copyTable2));
  Pair keys = findKeys(table1, table2);

  sort(copyTable1.begin(), copyTable1.end(), [keys](const Tuple& a, const Tuple& b) {
  return a[keys.first] < b[keys.first];
  });

  sort(copyTable2.begin(), copyTable2.end(), [keys](const Tuple& a, const Tuple& b) {
  return a[keys.second] < b[keys.second];
  });
  int mark = 999;
  int table1idx = 1;
  int table2idx = 1;

  do {

    if (mark == 999) {
      while(copyTable1[table1idx][keys.first] < copyTable2[table2idx][keys.second]) {
          table1idx += 1;
          if (table1idx == copyTable1.size()){
              goto end;
          }
      }
      while(copyTable1[table1idx][keys.first] > copyTable2[table2idx][keys.second]) {
        table2idx += 1;
          if (table2idx == copyTable2.size()){
              goto end;
          }
      }
      mark = table2idx;
    }
    if (copyTable1[table1idx][keys.first] == copyTable2[table2idx][keys.second]) {
      Tuple match;
      copy(copyTable1[table1idx].begin(), copyTable1[table1idx].end(), back_inserter(match));
      match.insert(match.end(), copyTable2[table2idx].begin(), copyTable2[table2idx].end());
      match.erase(match.begin() + keys.first, match.begin() + (keys.first +1));
      presult.push_back(match);
      table2idx += 1;
    } else {
      table2idx = mark;
      table1idx += 1;
      mark = 999;
    }
  }
  while (table1idx < copyTable1.size() && table2idx < copyTable2.size());
    end:
  return presult;

}
