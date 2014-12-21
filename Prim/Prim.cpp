/* Kruskal algorithm -- a MST method
 * Adjacency matrix version
 * @author Xu
 * @date Dec,20,2014
 * inspried by geeksforgeeks solution
 * */

#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

#define NUM_OF_VERTICES 5

int getMinKey(const vector<int> key, const vector<bool> &mstSet)
{
   int min = INT_MAX;
   int min_index = 0;
   for (int i = 0; i < NUM_OF_VERTICES; i++)
   {
     if (mstSet[i] == false && key[i] < min)
     {
    	 min = key[i], min_index = i;
     }
   }
   return min_index;
}

void printMST(const vector<int> parent, int n, const vector<vector<int>> &graph)
{
   cout << "Edge   Weight" << endl;
   for (int i = 1; i < NUM_OF_VERTICES; i++){
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
   }
}

void generateMstPRIM(vector<vector<int> > &graph)
{
     vector<int> key(NUM_OF_VERTICES, INT_MAX);
     vector<bool> mstSet(NUM_OF_VERTICES, false);
     vector<int> parent(NUM_OF_VERTICES, 0);

     key[0] = 0;
     parent[0] = -1;


     for (int count = 0; count < NUM_OF_VERTICES-1; count++)
     {
        int u = getMinKey(key, mstSet);
        cout << "Got Min Key, it is: " << u << endl;
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < NUM_OF_VERTICES; v++)
        {
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if ( (graph[u][v]!=0) && mstSet[v] == false && graph[u][v] <  key[v])
          {
             parent[v]  = u, key[v] = graph[u][v];
          }
        }
     }

     // print the constructed MST
     printMST(parent, NUM_OF_VERTICES, graph);
}


//test program
int main()
{
   /* use this graph for testing.
          3    5
      (0)--(1)--(2)
       |   / \   |
      1| 2/   \9 |10
       | /     \ |
      (3)-------(4)
            4          */

	vector<vector<int> > graph = {
			{0, 3, 0, 1, 0},
            {3, 0, 5, 2, 9},
            {0, 5, 0, 0, 10},
            {1, 2, 0, 0, 4},
            {0, 9, 10, 4, 0},
           };

	generateMstPRIM(graph);
	return 0;
	//expected result
//	Edge   Weight
//	3 - 1    2
//	1 - 2    5
//	0 - 3    1
//	3 - 4    4

}



/**
        +-----+----+----+-----+----+       +------+------+------+-----+-----+
        |     |    |    |     |    |       |      |      |      |     |     |
Parent  |neg1 |neg1|neg1|neg1 |neg1|       | 0    | 3    | 0    | 1   | 0   |
        +-----+----+----+-----+----+       +--------------------------------+
                                           |      |      |      |     |     |
                                           | 3    | 0    | 5    | 2   | 9   |
        +-----+----+----+-----+----+       +--------------------------------+
        |     |    |    |     |    |       |      |      |      |     |     |
Key     | 0   | Max|Max |Max  |Max |       | 0    | 5    | 0    | 0   | 10  |
        +-----+----+----+-----+----+       +--------------------------------+
                                           |      |      |      |     |     |
                                           | 1    | 2    | 0    | 0   | 4   |
        +-----+----+----+-----+----+       +--------------------------------+
        |     |    |    |     |    |       | 0    | 9    | 10   | 4   | 0   |
mstSet  |true |f   |f   |f    |f   |       +------+------+------+-----+-----+
        +-----+----+----+-----+----+



u = 0, 3, 1, 4                        Every iteration, keep updating parent, key mstSet , three vectors.
                                      Always add vetex that has least key and not in mst yet to the MstSet.
v=0...4




 */
