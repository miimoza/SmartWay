#include "station.hh"

using adjacency_list =
    std::vector<std::pair<Station, std::pair<size_t, size_t>>>;

Station::Station(std::string name, std::string slug)
    : name_(name)
    , slug_(slug)
{}

void Station::add_line(std::string code)
{
    lines_.push_back(code);
}

std::vector<std::string> Station::get_lines()
{
    return lines_;
}

adjacency_list Station::get_ajds()
{
    return adj_stations_;
}

std::string Station::get_name()
{
    return name_;
}

std::string Station::get_slug()
{
    return slug_;
}
