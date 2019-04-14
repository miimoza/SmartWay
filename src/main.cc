#include <fstream>
#include <iostream>

#include "graph.hh"
#include "itinerary.hh"
#include "json.hpp"
#include "log.hh"
#include "utils.hh"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    init_logs();
    Log::display = false;

    std::cout << "Welcome to Smart Way\n";
    std::shared_ptr<Graph> G;
    G = create_graph();

    while (true)
    {
        init_dijkstra(G->station_list);
        smartway(G);
    }

    if (argc >= 3 && !strcmp(argv[1], "-d"))
        build_dot_file(G, argv[2]);
    return 0;
}
