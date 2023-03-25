#include <ogdf/basic/Graph.h>

ogdf::List<ogdf::AdjElement*> vecToList(const std::vector<ogdf::AdjElement*>& vec) {
    ogdf::List<ogdf::AdjElement*> list;
    for(int i = 0; i < list.size(); i++) {
        list.pushBack(vec[i]);
    }
    return list;
}

int main() {
    ogdf::Graph graph;
    auto v1 = graph.newNode();
    auto v2 = graph.newNode();
    auto v3 = graph.newNode();
    auto v4 = graph.newNode();
    graph.newEdge(v1, v2);
    graph.newEdge(v2, v3);
    graph.newEdge(v3, v4);
    graph.newEdge(v4, v1);
    graph.newEdge(v1, v3);
    graph.newEdge(v2, v4);

    std::vector<std::vector<ogdf::AdjElement*>> rotation_system(4);
    for (auto v: {v1, v2, v3, v4}) {
        std::cout << "node: " << v->index() << std::endl;
        for (auto adj: v->adjEntries) {
            rotation_system[v->index()].push_back(adj);
            std::cout << "\t" << v->index() << "->" << adj->theEdge()->opposite(v)->index() << std::endl;
        }
        std::sort(rotation_system[v->index()].begin(), rotation_system[v->index()].end());
    }

    auto embedding = 0;
    do {
        graph.sort(v1, vecToList(rotation_system[v1->index()]));
        do {
            graph.sort(v2, vecToList(rotation_system[v2->index()]));
            do {
                graph.sort(v3, vecToList(rotation_system[v3->index()]));
                do {
                    graph.sort(v4, vecToList(rotation_system[v4->index()]));
                    std::cout << "Genus: " << graph.genus() << std::endl;
                    embedding++;
                } while (std::next_permutation(rotation_system[v4->index()].begin(), rotation_system[v4->index()].end()));
            } while (std::next_permutation(rotation_system[v3->index()].begin(), rotation_system[v3->index()].end()));
        } while (std::next_permutation(rotation_system[v2->index()].begin(), rotation_system[v2->index()].end()));

    } while (std::next_permutation(rotation_system[v1->index()].begin(), rotation_system[v1->index()].end()));
    std::cout << "Total embedding: " << embedding << std::endl;
    return 0;
}
