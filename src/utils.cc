#include "utils.hh"

#include <fstream>
#include <iostream>
#include <string>

#include "graph.hh"
#include "station.hh"

static void build_dot_file_rec(std::shared_ptr<Station> S, std::ofstream& os)
{
    std::cout << "Build from " << S->get_name() << "\n";
    S->printed = 1;
    auto adjs = S->get_adjs();

    for (size_t i = 0; i < S->get_len_adjs(); i++)
    {
        auto child = adjs[i].second.first;
        std::string name_child = adjs[i].second.first->get_name();

        os << S->get_id() << "->" << child->get_id() << ";\n";
        os << S->get_id() << " [shape=rectangle, label=\"" << S->get_name()
           << "\"];\n";

        os << child->get_id() << " [shape=circle, style=filled, label=\""
           << name_child << "\"];\n";

        if (!child->printed)
            build_dot_file_rec(child, os);
    }
}

void build_dot_file(std::shared_ptr<Graph> G, const std::string& output_path)
{
    std::cout << "Build " << output_path << "\n";

    std::ofstream os;
    os.open(output_path);
    os << "digraph AST {\n";
    build_dot_file_rec(G->station_list[10], os);
    os << "}";
}
