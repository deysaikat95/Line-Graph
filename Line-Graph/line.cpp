#include<iostream>
#include<vector>
#include<map>
#include<utility>

struct Node {
    //node in the original graph
    int node, cost;
    Node(int _node, int _cost): node(_node), cost(_cost) {}
};

struct Edge {
    //edge in the original graph
    int node, cost;
    Edge(int _node, int _cost): node(_node), cost(_cost) {}
};

struct Graph {
    std::vector<Node> nodes;//list of nodes
    std::vector<Edge> adj_list[10];//Adjacency list representation of graph
    Graph() {
        nodes.clear();
        for(int i = 0;i < 10;i++)
            adj_list[i].clear();
    }
    void add_node(int node_id, int cost=-1) {
        //function to add node in the original graph
        Node nd(node_id, cost);
        nodes.push_back(nd);
    }
    void add_edge(int node1, int node2, int cost=-1) {
        //function to add edge in the original graph
        Edge e1(node1, cost), e2(node2, cost);
        adj_list[node1].push_back(e2);
        adj_list[node2].push_back(e1);
    }
};


//node in the transformed Line Graph.
struct TurnNode {
    int node1, node2, cost;
    //Each node in a turn is an edge of the original graph.
    TurnNode(int _node1, int _node2, int _cost): node1(_node1), node2(_node2), cost(_cost) {}
    TurnNode(Node node1, Edge e): node1(node1.node), node2(e.node), cost(e.cost) {}
};

//edge in the transformed line graph
struct TurnEdge {
    int node1, node2, node3, cost;
    /*
    Each turn is a tuple of nodes(node1, node2, node3) having an edge between node1 and node2 &&
    node2 and node3 with cost.
    */
    TurnEdge(int _node1, int _node2, int _node3, int _cost): node1(_node1), node2(_node2), node3(_node3), cost(_cost) {}
    TurnEdge(Edge e1, Node node2, Edge e2): node1(e1.node), node2(node2.node), node3(e2.node), cost(node2.cost) {}
    TurnEdge(Edge e1, int _node2, Edge e2, int _cost): node1(e1.node), node2(_node2), node3(e2.node), cost(_cost) {}
};

struct LineGraph {
    std::vector<TurnNode> nodes;
    std::vector<TurnEdge> edges;
    LineGraph() {
        nodes.clear();
        edges.clear();
    }
    //function that transforms the graph
    void transform(Graph G) {
        std::map< TurnEdge,bool > visited;
        for(auto &node: G.nodes) {
            for(auto &edge: G.adj_list[node.node]) {
                if(node.node < edge.node) {
                    TurnNode tn(node, edge);
                    nodes.push_back(tn);
                }
            }
            for(auto &edge1: G.adj_list[node.node]) {
                for(auto &edge2: G.adj_list[node.node]) {
                    if(edge1.node < edge2.node) {
                        TurnEdge te(edge1, node, edge2);
                        edges.push_back(te);
                    }
                }
            }
        }
    }
    //function that outputs the nodes of the resulting Line graph.
    void outputNodes() {
        for(auto &node: nodes) {
            printf("Node is formed using %d and %d of the original graph with cost %d\n", node.node1, node.node2, node.cost);
        }
    }
    //function that outputs the edges of the resulting Line graph.
    void outputEdges() {
        for(auto &edge: edges) {
            printf("Edge is formed using %d, %d and %d nodes with %d node acting as junction and the cost associated with this edge is %d\n",
                    edge.node1, edge.node2, edge.node3, edge.node2, edge.cost);
        }
    }
};


int main() {
    Graph G;
    G.add_node(1, 8);
    G.add_node(2, 7);
    G.add_node(3, 9);
    G.add_node(4, 6);
    G.add_node(5, 10);
    G.add_edge(1, 2, 8);
    G.add_edge(2, 5, 7);
    G.add_edge(4, 5, 10);
    G.add_edge(3, 4, 5);
    G.add_edge(1, 3, 9);
    G.add_edge(1, 4, 6);

    LineGraph LG;
    LG.transform(G);
    LG.outputNodes();
    LG.outputEdges();
    return 0;
}
