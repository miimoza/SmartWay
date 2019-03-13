#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "graph.hh"
#include "json.hpp"

using json = nlohmann::json;

json stream_to_json(const std::string& filename)
{
    std::cout << "parsing " << filename << "...\n";
    std::ifstream s(filename);

    json j;
    s >> j;

    return j;
}

std::vector<Station> init_stations()
{
    std::vector<Station> station_list;

    std::cout << "Init stations list...\n";
    json jsn_lines = stream_to_json("data/lines.json");

    for (auto l : jsn_lines["result"]["metros"])
    {
        std::stringstream line_path;
        std::string s(l["code"]);
        s.erase(remove(s.begin(), s.end(), '\"'), s.end());
        line_path << "data/stations/" << s << ".json";
        json line = stream_to_json(line_path.str());
        for (auto s_js : line["result"]["stations"])
        {
            // std::cout << "	Adding station " << s_js["slug"] << "\n";
            Station station(s_js["name"], s_js["slug"]);
            station.add_line(s);
            station_list.push_back(station);
        }
    }
}

Graph create_graph()
{
    Graph g;
    std::vector<Station> station_list = init_stations();
    std::cout << "letsgo\n";
    for (Station s : station_list)
    {
        std::cout << s.get_name() << "\n";
        for (auto l : s.get_lines())
            std::cout << s.get_name() << "avec la " << l << "\n";
    }

    return g;
}
