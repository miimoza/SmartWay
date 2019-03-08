#pragma once

#include "station.hh"

class Graph
{
public:
    Graph() = default;

private:
    std::vector<Station> station_list;
};

Graph create_graph();
