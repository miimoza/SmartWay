#pragma once

#include "station.hh"

class Graph
{
public:
    Graph() = default;
    std::vector<std::shared_ptr<Station>> station_list;
};

std::shared_ptr<Graph> create_graph();
