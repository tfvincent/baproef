#include <iostream>
#include <vector>
#include <iomanip>
#include "vectorUtil.h"
#include "leapfrog_join.h"
#include "genericJoin.h"
#include "leapfrog_triejoin.h"
#include "nestedLoopJoin.h"
#include "sortMergeJoin.h"
#include "benchmark.h"
#include "timer.h"
#include "join.h"
using namespace std;

int main() {

    /*********************************************************************************
     *                                   BENCHMARKING                                *
     *********************************************************************************/
    /**
     * DATA
     */
    int size = 14;
    int datasize = 100;
    vector<vector<int>> vars;
    vector<int> varOrder = {1, 2, 3};
    vector<int> ij = {1,2};
    vector<int> ik = {2,3};
    vector<int> il = {1,3};
    vars.push_back(ij);
    vars.push_back(ik);
    vars.push_back(il);

    /**
    * SKEW NO RESULT BENCHMARKING
    */
    printf("\n");
    printf("Benchmarking on skew data with no result: \n");

    /**
     * GENERIC JOIN SKEW NO RESULT DATA
     */
    unsigned long long averageGenericJoinSkewNoRes = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> pointers = generateNoSolutionSkew(size, vars);
            vector<Table> tablesNormalSkew;
            for (auto * x: pointers) {
                tablesNormalSkew.push_back(*x);
            }
            HyperGraph * hyperGraph = generateHyperGraph(tablesNormalSkew);
            Timer timer("Leapfrog triejoin");
            Table result = genericJoin(hyperGraph, tablesNormalSkew, 1);
            auto duration = timer.Stop();
            if (i > 1) {
                averageGenericJoinSkewNoRes = averageGenericJoinSkewNoRes + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time generic join on skew data with no result: "<< averageGenericJoinSkewNoRes/98 << "ns\n";

    /**
     * LEAPFROG JOIN SKEW NO RESULT DATA
     */
    unsigned long long averageLeapfrogSkewNoRes = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormalSkew = generateNoSolutionSkew(size, vars);
            vector<struct node *> rootNodesNewSkew = restartNodes(tablesNormalSkew);
            vector<TrieIterator*> triesSkew = restartTrieIterators(rootNodesNewSkew);
            vector<vector<TrieIterator*>> trieTableSkew = getTrieTable(triesSkew, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            Table result = leapfrogTriejoin(trieTableSkew, triesSkew);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrogSkewNoRes = averageLeapfrogSkewNoRes + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time leapfrog trie join on skew data with no result: "<< averageLeapfrogSkewNoRes/98 << "ns\n";

    /**
     * NESTED LOOP JOIN SKEW NO RESULT DATA
     */
    unsigned long long averageNestedSkewNoRes = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkew = generateNoSolutionSkew(size, vars);
            Table * table1Skew = tablesSkew[0];
            Table * table2Skew = tablesSkew[1];
            Table * table3Skew = tablesSkew[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1Skew, *table2Skew, *table3Skew, nestedLoopJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedSkewNoRes = averageNestedSkewNoRes + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time nested loop join on skew data with no result: "<< averageNestedSkewNoRes/98 << " ns\n";

    /**
     * SORT MERGE JOIN SKEW NO RESULT DATA
     */
    unsigned long long averageSortSkewNoRes = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkew = generateNoSolutionSkew(size, vars);
            Table * table1Skew = tablesSkew[0];
            Table * table2Skew = tablesSkew[1];
            Table * table3Skew = tablesSkew[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1Skew, *table2Skew, *table3Skew, sortMergeJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageSortSkewNoRes = averageSortSkewNoRes + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time sort merge join on skew data with no result: "<< averageSortSkewNoRes/98 << " ns\n";

    /**
    * SKEW BENCHMARKING
    */
    printf("\n");
    printf("Benchmarking on skew data: \n");

    /**
     * GENERIC JOIN SKEW DATA
     */
    unsigned long long averageGenericJoinSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> pointers = restartSkewTables(size, vars);
            vector<Table> tablesNormalSkew;
            for (auto * x: pointers) {
                tablesNormalSkew.push_back(*x);
            }
            HyperGraph * hyperGraph = generateHyperGraph(tablesNormalSkew);
            Timer timer("Leapfrog triejoin");
            Table result = genericJoin(hyperGraph, tablesNormalSkew, 1);
            auto duration = timer.Stop();
            if (i > 1) {
                averageGenericJoinSkew = averageGenericJoinSkew + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time generic join on skew data: "<< averageGenericJoinSkew/98 << "ns\n";

    /**
     * LEAPFROG JOIN SKEW DATA
     */
    unsigned long long averageLeapfrogSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormalSkew = restartSkewTables(size, vars);
            vector<struct node *> rootNodesNewSkew = restartNodes(tablesNormalSkew);
            vector<TrieIterator*> triesSkew = restartTrieIterators(rootNodesNewSkew);
            vector<vector<TrieIterator*>> trieTableSkew = getTrieTable(triesSkew, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            Table result = leapfrogTriejoin(trieTableSkew, triesSkew);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrogSkew = averageLeapfrogSkew + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time leapfrog trie join on skew data: "<< averageLeapfrogSkew/98 << "ns\n";

    /**
     * NESTED LOOP JOIN SKEW DATA
     */
    unsigned long long averageNestedSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkew = restartSkewTables(size, vars);
            Table * table1Skew = tablesSkew[0];
            Table * table2Skew = tablesSkew[1];
            Table * table3Skew = tablesSkew[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1Skew, *table2Skew, *table3Skew, nestedLoopJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedSkew = averageNestedSkew + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time nested loop join on skew data: "<< averageNestedSkew/98 << " ns\n";

    /**
     * NESTED LOOP JOIN SKEW DATA
     */
    unsigned long long averageSortSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkew = restartSkewTables(size, vars);
            Table * table1Skew = tablesSkew[0];
            Table * table2Skew = tablesSkew[1];
            Table * table3Skew = tablesSkew[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1Skew, *table2Skew, *table3Skew, sortMergeJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageSortSkew = averageSortSkew + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time sort merge join on skew data: "<< averageSortSkew/98 << " ns\n";

    /**
     * BENCHMARKING SKEW UNSORTED DATA
     */
    printf("\n");
    printf("Benchmarking on skew unsorted data: \n");

    /**
    * GENERIC JOIN SKEW UNSORTED DATA
    */
    unsigned long long averageGenericJoinSkewUnsorted = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> pointersUnsorted = restartSkewTablesUnsorted(size, vars);
            vector<Table> tablesNormalSkewUnsorted;
            HyperGraph * hyperGraphUnsorted = generateHyperGraph(tablesNormalSkewUnsorted);

            Timer timer("Leapfrog triejoin");
            Table result = genericJoin(hyperGraphUnsorted, tablesNormalSkewUnsorted, 1);
            auto duration = timer.Stop();

            if (i > 1) {
                averageGenericJoinSkewUnsorted = averageGenericJoinSkewUnsorted + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time generic join on skew unsorted data: "<< averageGenericJoinSkewUnsorted/98 << "ns\n";

    /**
     * LEAPFROG JOIN SKEW UNSORTED DATA
     */
    unsigned long long averageLeapfrogSkewUnsorted = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormalSkewUnsorted = restartSkewTablesUnsorted(size, vars);
            vector<struct node *> rootNodesNewSkewUnsorted = restartNodes(tablesNormalSkewUnsorted);
            vector<TrieIterator*> triesSkewUnsorted = restartTrieIterators(rootNodesNewSkewUnsorted);
            vector<vector<TrieIterator*>> trieTableSkewUnsorted = getTrieTable(triesSkewUnsorted, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            Table result = leapfrogTriejoin(trieTableSkewUnsorted, triesSkewUnsorted);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrogSkewUnsorted = averageLeapfrogSkewUnsorted + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time leapfrog trie join on skew unsorted data: "<< averageLeapfrogSkewUnsorted/98 << "ns\n";

    /**
     * NESTED LOOP JOIN SKEW UNSORTED DATA
     */
    unsigned long long averageNestedSkewUnsorted = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkewUnsorted = restartSkewTablesUnsorted(size, vars);
            Table * table1SkewUnsorted = tablesSkewUnsorted[0];
            Table * table2SkewUnsorted = tablesSkewUnsorted[1];
            Table * table3SkewUnsorted = tablesSkewUnsorted[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1SkewUnsorted, *table2SkewUnsorted, *table3SkewUnsorted, nestedLoopJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedSkewUnsorted = averageNestedSkewUnsorted + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time nested loop join on skew unsorted data: "<< averageNestedSkewUnsorted/98 << " ns\n";

    /**
     * SORT MERGE JOIN SKEW UNSORTED DATA
     */
    unsigned long long averageSortSkewUnsorted = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkewUnsorted = restartSkewTablesUnsorted(size, vars);
            Table * table1SkewUnsorted = tablesSkewUnsorted[0];
            Table * table2SkewUnsorted = tablesSkewUnsorted[1];
            Table * table3SkewUnsorted = tablesSkewUnsorted[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1SkewUnsorted, *table2SkewUnsorted, *table3SkewUnsorted, sortMergeJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageSortSkewUnsorted = averageSortSkewUnsorted + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time sort merge join on skew unsorted data: "<< averageSortSkewUnsorted/98 << " ns\n";

    /**
     * BENCHMARKING NORMAL DATA
     */
    printf("\n");
    printf("Benchmarking on normal data:\n");
    /**
     * GENERIC JOIN NORMAL DATA
     */
    unsigned long long averageGenericJoinNormal = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> pointersNormal = restartTables(size, vars, datasize);
            vector<Table> tablesNormalNormal;
            for (auto * x: pointersNormal) {
                tablesNormalNormal.push_back(*x);
            }
            HyperGraph * hyperGraph = generateHyperGraph(tablesNormalNormal);
            Timer timer("Leapfrog triejoin");
            Table result = genericJoin(hyperGraph, tablesNormalNormal, 1);
            auto duration = timer.Stop();
            if (i > 1) {
                averageGenericJoinNormal = averageGenericJoinNormal + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time generic join on normal data: "<< averageGenericJoinNormal/98 << "ns\n";

    /**
     * LEAPFROG JOIN NORMAL DATA
     */
    unsigned long long averageLeapfrog = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormal = restartTables(size, vars, datasize);
            vector<struct node *> rootNodesNew = restartNodes(tablesNormal);
            vector<TrieIterator*> tries = restartTrieIterators(rootNodesNew);
            vector<vector<TrieIterator*>> trieTable = getTrieTable(tries, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            Table result = leapfrogTriejoin(trieTable, tries);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrog = averageLeapfrog + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time leapfrog trie join on normal data: "<< averageLeapfrog/98 << "ns\n";

    /**
     * NESTED LOOPJOIN NORMAL DATA
     */
    unsigned long long averageNestedNormal = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormal = restartTables(size, vars, datasize);
            Table * table1 = tablesNormal[0];
            Table * table2 = tablesNormal[1];
            Table * table3 = tablesNormal[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1, *table2, *table3, nestedLoopJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedNormal = averageNestedNormal + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time nested loop join on normal data: "<< averageNestedNormal/98 << "ns\n";

    /**
 * SORT MERGE JOIN NORMAL DATA
 */
    unsigned long long averageSortNormal = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormal = restartTables(size, vars, datasize);
            Table * table1 = tablesNormal[0];
            Table * table2 = tablesNormal[1];
            Table * table3 = tablesNormal[2];
            Timer timer("Leapfrog triejoin");
            Table result = join(*table1, *table2, *table3, sortMergeJoin);
            auto duration = timer.Stop();
            if (i > 1) {
                averageSortNormal = averageSortNormal + duration;
            }
        }
    }
    cout<<setprecision (7) <<"Average time sort merge join on normal data: "<< averageSortNormal/98 << "ns\n";
    return 0;
}
