#include <fstream>
#include <iostream>

#include "graph.hh"
#include "json.hpp"
#include "utils.hh"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Welcome to IDF SIMULATOR\n";

    auto G = create_graph();
    build_dot_file(G, "output.dot");

    return 0;
}
