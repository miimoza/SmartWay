#pragma once


#include "json.hpp"
#include "station.hh"

using json = nlohmann::json;

using path_type = std::vector<std::shared_ptr<Station>>;
using station_vect = std::vector<std::shared_ptr<Station>>;

class Graph
{
public:
    Graph() = default;
    std::vector<std::shared_ptr<Station>> station_list;
    json lines_;
};

std::shared_ptr<Graph> create_graph();
std::shared_ptr<Station> get_station(station_vect v, const std::string& slug);
void init_dijkstra(station_vect v);
