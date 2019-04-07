#pragma once

#include "json.hpp"
#include "station.hh"
using json = nlohmann::json;

class Graph
{
public:
    Graph() = default;
    std::vector<std::shared_ptr<Station>> station_list;
    json lines_;
};

std::shared_ptr<Graph> create_graph();
