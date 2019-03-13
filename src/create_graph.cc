#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "graph.hh"
#include "json.hpp"

using json = nlohmann::json;
using station_vect = std::vector<std::shared_ptr<Station>>;
using adjacency_station =
    std::pair<std::string,
              std::pair<std::shared_ptr<Station>, std::pair<size_t, size_t>>>;
using adjacency_list = std::vector<adjacency_station>;

static json stream_to_json(const std::string& filename)
{
    std::cout << "parsing " << filename << "...\n";
    std::ifstream s(filename);

    json j;
    s >> j;

    return j;
}

static std::shared_ptr<Station> get_station(station_vect v,
                                            const std::string& slug)
{
    for (auto s : v)
        if (!slug.compare(s->get_slug()))
            return s;
    return NULL;
}

static void fill_adj_station(station_vect v, std::shared_ptr<Station> s, json l,
                             const std::string& line_code, size_t i)
{
    std::cout << "station " << i << l.size() << l[i]["slug"] << "\n";
    std::string slug = l[i]["slug"];

    std::shared_ptr<Station> s1, s2;
    if (i < l.size() - 1)
    {
        std::cout << "	avant " << i << l.size() << l[i + 1]["slug"] << "\n";
        s1 = get_station(v, l[i + 1]["slug"]);
        adjacency_station adj1 = std::make_pair(
            line_code, std::make_pair(s1, std::make_pair(0, 60)));
        s->add_adj(adj1);
    }

    if (i > 0)
    {
        std::cout << "	apres " << i << l.size() << l[i - 1]["slug"] << "\n";
        s2 = get_station(v, l[i - 1]["slug"]);
        adjacency_station adj2 = std::make_pair(
            line_code, std::make_pair(s2, std::make_pair(0, 60)));
        s->add_adj(adj2);
    }
}

static void update_adj_lists(station_vect v)
{
    json jsn_lines = stream_to_json("data/lines.json");
    for (auto l : jsn_lines["result"]["metros"])
    {
        std::stringstream line_path;
        std::string s(l["code"]);
        s.erase(remove(s.begin(), s.end(), '\"'), s.end());
        line_path << "data/stations/" << s << ".json";
        json line = stream_to_json(line_path.str());
        l = line["result"]["stations"];
        for (size_t i = 0; i < l.size(); i++)
        {
            auto station = get_station(v, l[i]["slug"]);
            if (!station)
                std::cerr << "error no station named " << l[i]["slug"] << "\n";
            else
                fill_adj_station(v, station, l, s, i);
        }
    }
}

static void update_id(station_vect v)
{
    for (size_t i = 0; i < v.size(); i++)
        v[i]->set_id(i);
}

static station_vect init_stations()
{
    station_vect station_list;

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
            std::cout << "	Adding station " << s_js["slug"] << "\n";
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

std::shared_ptr<Graph> create_graph()
{
    std::shared_ptr<Graph> g = std::make_shared<Graph>();
    g->station_list = init_stations();
    update_adj_lists(g->station_list);
    update_id(g->station_list);

    for (auto s : g->station_list)
    {
        for (auto l : s->get_lines())
            std::cout << s->get_name() << " avec la " << l << "\n";
        for (auto a : s->get_adjs())
            std::cout << "		ajdacent a " << a.second.first->get_name()
                      << " sur la ligne " << a.first << "\n";
    }

    return g;
}
