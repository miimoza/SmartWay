#include "graph.hh"

using adjacency_station =
    std::pair<std::string,
              std::pair<std::shared_ptr<Station>, std::pair<size_t, size_t>>>;

path_type get_path(std::shared_ptr<Graph> G, std::string src_station,
                   std::string dst_station);

void smartway(std::shared_ptr<Graph> G);
