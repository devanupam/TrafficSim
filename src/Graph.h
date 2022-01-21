#pragma once

#include <string>
#include <vector>
#include "MapUtil.h"

namespace ADSB {

class Graph
{
private:
    std::vector<std::vector<Position>> adjVec;

public:
    Graph(/* args */);
    Graph(std::string csv_file_name);

    void addEdge(Position u, Position v);
    void print(int V);
    void generateGraph();

    ~Graph();
};


}