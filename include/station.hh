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
    Station();

private:
    std::string name;
    std::string slug;

    adjacency_list adj_list;
};
