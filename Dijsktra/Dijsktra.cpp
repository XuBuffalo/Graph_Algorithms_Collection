/* Dijkstra algorithm -- Find shortest path in directed graph
 *
 * @author Xu
 * @date Dec,21st,2014
 *
 * */
//
//Very similar to Prim algorithm.
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
using namespace std;

#define NUM_OF_VERTICES 5

int getMinKey(const vector<int>& key, const vector<bool> &mstSet)
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

// print result
void printShortestPath(vector<int> dist, int n)
{
    cout << "Shortest path weight from source:" << endl;
    for (int i = 0; i < n; ++i){
    	cout << i << "  " << dist[i] << endl;
    }
}

void Dijkstra(vector<vector<int> > &graph)
{
	 //INITIALIZE_SINGLE_SOURCE(G, s)

     vector<int> shortest_path_estimation(NUM_OF_VERTICES, INT_MAX);
     vector<bool> mstSet(NUM_OF_VERTICES, false);

     shortest_path_estimation[0] = 0;


     for (int count = 0; count < NUM_OF_VERTICES-1; count++)
     {
        int u = getMinKey(shortest_path_estimation, mstSet);
        cout << "Got Min Key, it is: " << u << endl;
        mstSet[u] = true;

        // for each vertex v in G.adj[u] RELAX(u,v,w)
        for (int i = 0; i < NUM_OF_VERTICES; i++)
        {
        	if(graph[u][i] != 0)
        	{
                int weight = graph[u][i];
                if (shortest_path_estimation[u] != INT_MAX && shortest_path_estimation[u] + weight < shortest_path_estimation[i]){
                    shortest_path_estimation[i] = shortest_path_estimation[u] + weight;
                }
        	}

        }

     }
     // print the constructed MST
     printShortestPath(shortest_path_estimation, NUM_OF_VERTICES);
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

	Dijkstra(graph);
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
