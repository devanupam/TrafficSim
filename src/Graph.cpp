#include "Graph.h"
#include <iostream>
#include "CSVReader.h"

namespace ADSB {


Graph::Graph(std::string csv_file_name) {
    FILE* fp = fopen(csv_file_name.c_str(), "rb"); // non-Windows use "r"

}

// A utility function to add an edge in an
// undirected graph.
void Graph::addEdge(Position u, Position v)
{
    adjVec[u].push_back(v);
    adjVec[v].push_back(u);
}
  
// A utility function to print the adjacency list
// representation of graph
void Graph::print(int V)
{
    for (int v = 0; v < V; ++v)
    {
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adjVec[v])
           std::cout << "-> " << x;
        printf("\n");
    }
}

}