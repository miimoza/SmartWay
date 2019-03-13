#pragma once

#include <string>
#include <utility>
#include <vector>

class Station
{
    // <Station, <Temps de changement + Temps d'Attente, Temps de parcours>>
    using adjacency_list =
        std::vector<std::pair<Station, std::pair<size_t, size_t>>>;

public:
    Station(std::string name, std::string slug);
    void add_line(std::string code);
    std::vector<std::string> get_lines();
    adjacency_list get_ajds();
    std::string get_name();
    std::string get_slug();

private:
    adjacency_list adj_stations_;
    std::vector<std::string> lines_;
    std::string name_;
    std::string slug_;
};
