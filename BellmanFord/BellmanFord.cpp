/* Bellman-Ford algorithm -- Find shortest path in directed graph
 *
 * @author Xu
 * @date Dec,21st,2014
 *
 * */
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <climits>

using namespace std;

class Edge
{
public:
	int src, dst, weight;
};

class Graph
{
	public:
	bool initGraph(int V, int E);
	bool BellmanFord( int src);
public:
	int V, E;
	vector<Edge> edges;
};

bool Graph::initGraph(int V, int E)
{
	this->V = V;
	this->E = E;
	edges.resize(E);
	return true;
}


// print result
void printShortestPath(vector<int> dist, int n)
{
    cout << "Shortest path weight from source:" << endl;
    for (int i = 0; i < n; ++i){
    	cout << i << "  " << dist[i] << endl;
    }
}

// BellmanFord algorithm. Find shortest path, single source.
// It can detect negative cycles too.
// O(VE) time complexity.
// Can be improved by using Dijkstra algorithm.

bool Graph::BellmanFord(int src)
{
    int V = this->V;
    int E = this->E;
    vector<int> shortest_path_estimation(V,INT_MAX);

    // INITILIZE-SINGLE_SOURCE(G, s)
    // for each vertex v in G.V
    //     v.d = INIFINITY
    //     v.pi = NIL
    // s.d = 0
//    for (int i = 0; i < V; i++)
//        shortest_path_estimation[i]   = INT_MAX;
    shortest_path_estimation[src] = 0;

    // Relax edges. Do it V-1 times.
    /*
     * RELAX（u，v, w)
     * 	if v.d > u.d + w(u,v)
     * 		v.d = u.d + w(u,v)
     * 		v.pi = u
     *
     * */
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = this->edges[j].src;
            int v = this->edges[j].dst;
            int weight = this->edges[j].weight;
            if (shortest_path_estimation[u] != INT_MAX && shortest_path_estimation[u] + weight < shortest_path_estimation[v]){
                shortest_path_estimation[v] = shortest_path_estimation[u] + weight;
            }
        }
    }
    // check negative cycles
    for (int i = 0; i < E; i++)
    {
        int u = this->edges[i].src;
        int v = this->edges[i].dst;
        int weight = this->edges[i].weight;
        if (shortest_path_estimation[u] != INT_MAX && shortest_path_estimation[u] + weight < shortest_path_estimation[v]){
            return false;
        }
    }

    printShortestPath(shortest_path_estimation, V);
    return true;
}

// Driver program to test above functions
int main()
{
    /* Let us create the graph given in above example */
    int V = 6;  // Number of vertices in graph
    int E = 8;  // Number of edges in graph

	Graph graph;
	graph.initGraph(V,E);

	/* Let us create following weighted graph
		  10        6
	 0--------1--------5
	 |  \     |        |
	6|   5\   |15      | 2
	 |      \ |    3   |
	 2--------3 -------4
		 4       */
	graph.edges[0].src = 0;
	graph.edges[0].dst = 1;
	graph.edges[0].weight = 10;

	// add edge 0-2
	graph.edges[1].src = 0;
	graph.edges[1].dst = 2;
	graph.edges[1].weight = 6;

	// add edge 0-3
	graph.edges[2].src = 0;
	graph.edges[2].dst = 3;
	graph.edges[2].weight = 5;

	// add edge 1-3
	graph.edges[3].src = 1;
	graph.edges[3].dst = 3;
	graph.edges[3].weight = 15;

	// add edge 2-3
	graph.edges[4].src = 2;
	graph.edges[4].dst = 3;
	graph.edges[4].weight = 4;

	// add edge 3-4
	graph.edges[5].src = 3;
	graph.edges[5].dst = 4;
	graph.edges[5].weight = 3;

	// add edge 1-5
	graph.edges[6].src = 1;
	graph.edges[6].dst = 5;
	graph.edges[6].weight = 6;

	// add edge 4-5
	graph.edges[7].src = 4;
	graph.edges[7].dst = 5;
	graph.edges[7].weight = 2;


    bool ret = graph.BellmanFord( 0);
    if(ret)
    	cout <<"Ran BellmanFord algorithm successful." << endl;
    else
    	cout << "This graph contains negative cycle(s)"<< endl;
    return 0;
}
