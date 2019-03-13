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

std::string Station::get_name()
{
    return name_;
}

std::string Station::get_slug()
{
    return slug_;
}
