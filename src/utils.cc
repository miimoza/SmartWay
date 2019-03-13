#include "utils.hh"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "graph.hh"
#include "station.hh"

std::map<std::string, std::string> line_colors = {
    {"1", "#FFCD00"},  {"2", "#003CA6"},  {"3", "#837902"},  {"3b", "#6EC4E8"},
    {"4", "#CF009E"},  {"5", "#FF7E2E"},  {"6", "#6ECA97"},  {"7", "#FA9ABA"},
    {"7b", "#6ECA97"}, {"8", "#E19BDF"},  {"9", "#B6BD00"},  {"10", "#C9910D"},
    {"11", "#704B1C"}, {"12", "#007852"}, {"13", "#6EC4E8"}, {"14", "#62259D"}};

static void build_dot_file_rec(std::shared_ptr<Graph> G,
                               std::shared_ptr<Station> S, std::ofstream& os)
{
    for (auto S : G->station_list)
    {
        std::cout << "Build from " << S->get_name() << "\n";
        S->printed = 1;
        auto adjs = S->get_adjs();

        for (size_t i = 0; i < S->get_len_adjs(); i++)
        {
            auto child = adjs[i].second.first;
            std::string name_child = adjs[i].second.first->get_name();

            std::string edge_color = line_colors[adjs[i].first];
            os << S->get_id() << "->" << child->get_id()
               << "[  penwidth=3, color=\"" << edge_color << "\"];\n";

            // os << S->get_id() << " [shape=box  , label=\"" << S->get_name()
            // /  << "\"];\n";

            os << child->get_id() << " [shape=box  , style=filled, label=\""
               << name_child << "\"];\n";

            // if (!child->printed)
            //    build_dot_file_rec(child, os);
        }
    }
}

void build_dot_file(std::shared_ptr<Graph> G, const std::string& output_path)
{
    std::cout << "Build " << output_path << "\n";

    std::ofstream os;
    os.open(output_path);
    os << "digraph AST {\n";
    build_dot_file_rec(G, G->station_list[10], os);
    os << "}";
}
