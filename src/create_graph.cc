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
    try
    {
        s >> j;
    } catch (std::exception& e)
    {
        std::cerr << "Error Parsing Json: cannot load " << filename << "\n";
    }
    s.close();

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

static void update_adj_lists(station_vect v, const std::string& type)
{
    json jsn_lines = stream_to_json("data/lines.json");
    for (auto l : jsn_lines["result"][type])
    {
        std::stringstream line_path;
        std::string code(l["code"]);
        code.erase(remove(code.begin(), code.end(), '\"'), code.end());
        line_path << "data/stations/" << type << "/" << code << ".json";
        json line = stream_to_json(line_path.str());
        l = line["result"]["stations"];
        for (size_t i = 0; i < l.size(); i++)
        {
            auto station = get_station(v, l[i]["slug"]);
            std::stringstream line_id;
            line_id << type << code;
            if (!station)
                std::cerr << "error no station named " << l[i]["slug"] << "\n";
            else
                fill_adj_station(v, station, l, line_id.str(), i);
        }
    }
}

static void update_id(station_vect v)
{
    for (size_t i = 0; i < v.size(); i++)
        v[i]->set_id(i);
}

static station_vect init_stations(station_vect station_list,
                                  const std::string& type)
{
    std::cout << "Init stations list...\n";
    json jsn_lines = stream_to_json("data/lines.json");

    for (auto l : jsn_lines["result"][type])
    {
        std::stringstream line_path;
        std::string code(l["code"]);
        code.erase(remove(code.begin(), code.end(), '\"'), code.end());
        line_path << "data/stations/" << type << "/" << code << ".json";
        json line = stream_to_json(line_path.str());
        for (auto s_js : line["result"]["stations"])
        {
            std::cout << "	Adding station " << s_js["slug"] << "\n";
            auto station = get_station(station_list, s_js["slug"]);
            if (!station)
            {
                std::shared_ptr<Station> station =
                    std::make_shared<Station>(s_js["name"], s_js["slug"]);

                std::stringstream line_id;
                line_id << type << code;

                station->add_line(line_id.str());
                station_list.push_back(station);
            } else
            {
                std::stringstream line_id;
                line_id << type << code;
                station->add_line(line_id.str());
            }
        }
    }

    return station_list;
}

static station_vect init_vector()
{
    station_vect station_list;

    station_list = init_stations(station_list, "metros");
    station_list = init_stations(station_list, "rers");
    station_list = init_stations(station_list, "tramways");
    station_list = init_stations(station_list, "bus");

    return station_list;
}

static void correct_failure(station_vect v)
{
    std::cout << "Correcting failure...\n";
}

std::shared_ptr<Graph> create_graph()
{
    std::shared_ptr<Graph> g = std::make_shared<Graph>();
    g->station_list = init_vector();

    update_adj_lists(g->station_list, "metros");
    update_adj_lists(g->station_list, "rers");
    update_adj_lists(g->station_list, "tramways");
    update_adj_lists(g->station_list, "bus");

    update_id(g->station_list);

    correct_failure(g->station_list);

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
