#include <fstream>
#include <iostream>

#include "graph.hh"
#include "itinerary.hh"
#include "json.hpp"
#include "utils.hh"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Welcome to Smart Way\n";

    auto G = create_graph();

    while (true)
        smartway(G);

    if (argc >= 3 && !strcmp(argv[1], "-d"))
        build_dot_file(G, argv[2]);
    return 0;
}
