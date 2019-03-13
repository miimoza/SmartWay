#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "graph.hh"
#include "json.hpp"

using json = nlohmann::json;
using stations_vect = std::vector<std::shared_ptr<Station>>;

json stream_to_json(const std::string& filename)
{
    std::cout << "parsing " << filename << "...\n";
    std::ifstream s(filename);

    json j;
    s >> j;

    return j;
}

std::shared_ptr<Station> get_station(stations_vect v, const std::string& slug)
{
    for (auto s : v)
        if (!slug.compare(s->get_slug()))
            return s;
    return NULL;
}

stations_vect init_stations()
{
    stations_vect station_list;

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
            auto station = get_station(station_list, s_js["slug"]);
            if (!station)
            {
                std::shared_ptr<Station> station =
                    std::make_shared<Station>(s_js["name"], s_js["slug"]);
                station->add_line(s);
                station_list.push_back(station);
            } else
            {
                station->add_line(s);
            }
        }
    }

    return station_list;
}

Graph create_graph()
{
    Graph g;
    stations_vect station_list = init_stations();
    std::cout << "letsgo\n";
    for (auto s : station_list)
        for (auto l : s->get_lines())
            std::cout << s->get_name() << " avec la " << l << "\n";

    return g;
}
