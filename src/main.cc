#include <fstream>
#include <iostream>

#include "graph.hh"
#include "json.hpp"
using json = nlohmann::json;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Welcome to IDF SIMULATOR\n";

    Graph g = create_graph();

    return 0;
}
