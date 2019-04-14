#include "itinerary.hh"

#include <iostream>

#include "graph.hh"
#include "log.hh"
#include "utils.hh"

static void print_path(path_type path)
{
    for (size_t i = 0; i < path.size(); i++)
        std::cout << "Station [" << i << "] : " << path[i]->get_name() << "\n";
}

static int get_cost(std::shared_ptr<Station> A, adjacency_station B)
{
    int cost = 0;
    std::string current_line =
        A->get_best_parent()->get_adj_line(A->get_slug());
    if (strcmp(current_line.c_str(), B.first.c_str()))
        cost = 5;
    cost = 2;
    return cost;
}

static void propagate(std::shared_ptr<Station> S,
                      std::shared_ptr<Station> destination)
{
    S->set_visited();
    if (S == destination)
        return;

    adjacency_station adjStation;
    std::shared_ptr<Station> nextStation;
    int new_path_value;

    for (size_t i = 0; i < S->get_adj_size(); i++)
    {
        adjStation = S->get_adj_index(i);
        if (!adjStation.second.first->is_visited())
        {
            new_path_value = S->get_path_value() + get_cost(S, adjStation);
            if (new_path_value < adjStation.second.first->get_path_value())
            {
                adjStation.second.first->set_path_value(new_path_value);
                adjStation.second.first->set_best_parent(S);
            }
            if (!nextStation
                || adjStation.second.first->get_path_value()
                    < nextStation->get_path_value())
            {
                nextStation = adjStation.second.first;
            }
        }
    }
}

static bool all_stations_visited(std::shared_ptr<Graph> G)
{
    for (auto s : G->station_list)
        if (!s->is_visited())
            return false;
    return true;
}

static path_type build_path(std::shared_ptr<Station> dst)
{
    path_type path;
    while (dst)
    {
        path.push_back(dst);
        dst = dst->get_best_parent();
    }
    return path;
}

static std::shared_ptr<Station> get_min_station(std::shared_ptr<Graph> G)
{
    Log l("minimum station");
    l << "lets go find the minimum station very good stuff to do\n";
    size_t i = 0;
    while (i < G->station_list.size() && G->station_list[i]->is_visited())
        i++;

    auto min = G->station_list[i];
    l << "test\n";
    for (; i < G->station_list.size(); i++)
    {
        l << "test" << i << "\n";
        if (!G->station_list[i]->is_visited()
            && G->station_list[i]->get_path_value() < min->get_path_value())
            min = G->station_list[i];
    }
    l << "test2\n";

    return min;
}

path_type get_path(std::shared_ptr<Graph> G, std::shared_ptr<Station> src,
                   std::shared_ptr<Station> dst)
{
    Log l("main loop");
    l << "Begining...\n";
    src->set_path_value(0);
    std::shared_ptr<Station> min;
    l << "test\n";
    while (!all_stations_visited(G))
    {
        min = get_min_station(G);
        l << "new min :" << min->get_name() << "\n";
        propagate(min, dst);
    }
    l << "test2\n";

    auto path = build_path(dst);
    print_path(path);

    return path;
}

void smartway(std::shared_ptr<Graph> G)
{
    Log l("SmartWay");
    Log l2("SmartWay", true);
    l << "Lets go find a itinerary\n";

    std::string src_station;
    std::string dst_station;

    std::cout << "Station de Départ: ";
    std::getline(std::cin, src_station);
    src_station = to_slug(src_station);
    auto src = get_station(G->station_list, src_station);
    if (!src)
    {
        l2 << src_station << " not valid...\n";
        return;
    }

    std::cout << "Station d'Arrivé: ";
    std::getline(std::cin, dst_station);
    dst_station = to_slug(dst_station);
    auto dst = get_station(G->station_list, dst_station);
    if (!dst)
    {
        l2 << dst_station << " not valid...\n";
        return;
    }

    get_path(G, src, dst);
}
