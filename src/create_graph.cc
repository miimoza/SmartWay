#include <fstream>
#include <iostream>
#include <string>

#include "graph.hh"
#include "json.hpp"

using json = nlohmann::json;

json stream_to_json(std::string filename)
{
    std::cout << filename << " converting to json structure\n";
    std::ifstream s(filename);

    std::cout << s.rdbuf();

    json j;
    s >> j;

    std::cout << "test:" << j["result"]["metros"][0]["code"] << "\n";

    return j;
}

std::vector<Station> init_stations()
{
    std::cout << "Init stations list...\n";
    json jsn_lines = stream_to_json("config.json");
}

Graph create_graph()
{
    Graph g;
    std::vector<Station> station_list = init_stations();

    return g;
}
