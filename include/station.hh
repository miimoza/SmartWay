#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Station
{
    // <Station, <Temps de changement + Temps d'Attente, Temps de parcours>>
    using adjacency_station = std::pair<
        std::string,
        std::pair<std::shared_ptr<Station>, std::pair<size_t, size_t>>>;
    using adjacency_list = std::vector<adjacency_station>;

public:
    Station(std::string name, std::string slug);
    void add_line(std::string code);
    void add_adj(adjacency_station adj);
    void set_id(size_t id);
    std::vector<std::string> get_lines();
    adjacency_list get_adjs();
    size_t get_len_adjs();
    std::shared_ptr<Station> get_adj(const std::string& slug);
    std::string get_name();
    size_t get_id();
    std::string get_slug();

    int printed = 0;

private:
    adjacency_list adj_stations_;
    std::vector<std::string> lines_;
    std::string name_;
    std::string slug_;
    std::size_t id_;
};
