#include <ogdf/basic/Graph.h>

ogdf::List<ogdf::AdjElement *> vecToList(const std::vector<ogdf::AdjElement *> &vec) {
    ogdf::List<ogdf::AdjElement *> list;
    for (auto i : vec) {
        list.pushBack(i);
    }
    return list;
}

class EnumerateEmbedding {
    int numberOfNodes;
    std::vector<ogdf::NodeElement *> nodes;
    std::vector<std::vector<ogdf::AdjElement *>> rotation_system;
    ogdf::Graph &m_G;
    int embedding = 0;
    std::function<void()> m_callback;
public:
    explicit EnumerateEmbedding(ogdf::Graph &G, const std::function<void()> &callback) : m_G(G), m_callback(callback) {
        numberOfNodes = m_G.numberOfNodes();
        rotation_system = std::vector<std::vector<ogdf::AdjElement *>>(numberOfNodes);
        for (auto v: m_G.nodes) {
            nodes.push_back(v);
            for (auto adj: v->adjEntries) {
                rotation_system[v->index()].push_back(adj);
            }
            std::sort(rotation_system[v->index()].begin(), rotation_system[v->index()].end());
        }
    }

    int enumerate(int node = 0) {
        if (node == 0) {
            embedding = 0;
        }
        do {
            m_G.sort(nodes[node], vecToList(rotation_system[node]));
            if (node == numberOfNodes - 1) {
                m_callback();
                embedding++;
            } else if (node < numberOfNodes - 1) {
                enumerate(node + 1);
            }
        } while (std::next_permutation(rotation_system[node].begin(), rotation_system[node].end()));

        return embedding;
    }
};

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

    EnumerateEmbedding enumerator(graph, [&]() {
        std::cout << "Graph's genus = " << graph.genus() << std::endl;
    });
    std::cout << enumerator.enumerate() << std::endl;
}
