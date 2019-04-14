#include "station.hh"

using adjacency_station =
    std::pair<std::string,
              std::pair<std::shared_ptr<Station>, std::pair<size_t, size_t>>>;
using adjacency_list = std::vector<adjacency_station>;

Station::Station(std::string name, std::string slug)
    : name_(name)
    , slug_(slug)
{}

void Station::add_line(std::string code)
{
    lines_.push_back(code);
}

void Station::add_adj(adjacency_station adj)
{
    adj_stations_.push_back(adj);
}

void Station::set_id(size_t id)
{
    id_ = id;
}

std::vector<std::string> Station::get_lines()
{
    return lines_;
}

adjacency_list Station::get_adjs()
{
    return adj_stations_;
}

size_t Station::get_id()
{
    return id_;
}

size_t Station::get_len_adjs()
{
    return adj_stations_.size();
}

std::shared_ptr<Station> Station::get_adj(const std::string& slug)
{
    for (auto s : adj_stations_)
        if (!slug.compare(s.second.first->get_slug()))
            return s.second.first;
    return NULL;
}

adjacency_station Station::get_adj_index(size_t i)
{
    return adj_stations_[i];
}

size_t Station::get_adj_size()
{
    return adj_stations_.size();
}

std::string Station::get_adj_line(const std::string& slug)
{
    for (auto s : adj_stations_)
        if (!slug.compare(s.second.first->get_slug()))
            return s.first;
    return NULL;
}

std::string Station::get_name()
{
    return name_;
}

std::string Station::get_slug()
{
    return slug_;
}

// DIJKSTRA STUFF

bool Station::is_visited()
{
    return visited_;
}

void Station::set_visited()
{
    visited_ = true;
}

std::shared_ptr<Station> Station::get_best_parent()
{
    return best_parent_;
}

void Station::set_best_parent(std::shared_ptr<Station> S)
{
    best_parent_ = S;
}

int Station::get_path_value()
{
    return path_value_;
}

void Station::set_path_value(int n)
{
    path_value_ = n;
}
