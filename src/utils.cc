#include "utils.hh"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "graph.hh"
#include "log.hh"
#include "station.hh"

std::map<std::string, std::string> line_colors = {
    {"metros1", "#FFCD00"},    {"metros2", "#003CA6"},
    {"metros3", "#837902"},    {"metros3b", "#6EC4E8"},
    {"metros4", "#CF009E"},    {"metros5", "#FF7E2E"},
    {"metros6", "#6ECA97"},    {"metros7", "#FA9ABA"},
    {"metros7b", "#6ECA97"},   {"metros8", "#E19BDF"},
    {"metros9", "#B6BD00"},    {"metros10", "#C9910D"},
    {"metros11", "#704B1C"},   {"metros12", "#007852"},
    {"metros13", "#6EC4E8"},   {"metros14", "#62259D"},
    {"rersA", "#E2231A"},      {"rersB", "#7BA3DC"},
    {"rersC", "#C9910D"},      {"rersD", "#00AE41"},
    {"rersE", "#E37ED1"},      {"tramways1", "#003CA6"},
    {"tramways2", "#CF009E"},  {"tramways3a", "#FF7E2E"},
    {"tramways3b", "#00AE41"}, {"tramways4", "#E19BDF"},
    {"tramways5", "grey"},     {"tramways6", "grey"},
    {"tramways7", "#704B1C"},  {"tramways8", "#837902"}};

static void build_dot_file_rec(std::shared_ptr<Graph> G, std::ofstream& os)
{
    Log log("Dot File");

    for (auto S : G->station_list)
    {
        log << "Build from " << S->get_name() << "\n";
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
            if (adjs[i].second.first->get_len_adjs() > 2)
                edge_color = "grey";

            os << child->get_id()
               << " [shape=box  , style=\"filled\", fillcolor=\"" << edge_color
               << "\", label=<<B>" << name_child << "</B>>];\n";

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
    os << "digraph AST {\nranksep=0.25;\nnodesep=0.5;\n";
    build_dot_file_rec(G, os);
    os << "}";
}
