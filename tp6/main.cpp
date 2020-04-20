#include <cstdio>
#include <graphviewer.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "src/animation_util.h"
#include "src/string_util.h"

void exercise1();

void exercise2();

void exercise3();

void exercise1() {
    auto *gv = new GraphViewer(600, 600, true);

    // gv->setBackground("background.jpg"); there is no background in the resources folder. I don't know what to do *shrug face*
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0);
    gv->addNode(1);
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 0, EdgeType::DIRECTED);

    gv->removeNode(1);

    gv->addNode(2);
    gv->addEdge(2, 0, 2, EdgeType::DIRECTED);
    gv->setVertexLabel(2, "This is a node!");
    gv->setEdgeLabel(2, "This is an edge!");
    gv->setEdgeColor(2, "yellow");

    gv->rearrange();
}

void exercise2() {
    // Setting up the windows
    auto *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    // Adding nodes to the graph
    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);

    // Adding edges to the graph
    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);

    gv->rearrange();

    /*_sleep(1000);

    gv->removeNode(12);
    gv->removeNode(13);

    gv->rearrange();

    _sleep(1000);

    gv->addNode(14, 250, 550);
    gv->addNode(15, 350, 550);

    gv->rearrange();*/

    animate(gv, 20);
}

void exercise3() {
    auto *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    // Reading nodes
    std::ifstream input_nodes("../resources/mapa1/nos.txt");

    if (!input_nodes.is_open()) {
        cerr << "Could not open the nodes file!" << endl;
    }

    std::string line;

    while (getline(input_nodes, line)) {
        std::vector<std::string> out;

        tokenize(line, ';', out);

        if (out.size() != 3) continue;

        if (!is_number(out[0]) || !is_number(out[1]) || !is_number(out[2])) continue;

        gv->addNode(strtol(out[0].c_str(), NULL, 0), strtol(out[1].c_str(), NULL, 0), strtol(out[2].c_str(), NULL, 0));
        cout << "Read a node: " << strtol(out[0].c_str(), NULL, 0) << ", " << strtol(out[1].c_str(), NULL, 0) << ", "
             << strtol(out[2].c_str(), NULL, 0)
             << endl;
    }

    // Reading edges
    std::ifstream input_edges("../resources/mapa1/arestas.txt");

    if (!input_edges.is_open()) {
        cerr << "Could not open the edges file!" << endl;
    }

    while (getline(input_edges, line)) {
        std::vector<std::string> out;

        tokenize(line, ';', out);

        if (out.size() != 3) continue;

        if (!is_number(out[0]) || !is_number(out[1]) || !is_number(out[2])) continue;

        gv->addEdge(strtol(out[0].c_str(), NULL, 0), strtol(out[1].c_str(), NULL, 0), strtol(out[2].c_str(), NULL, 0),
                    EdgeType::UNDIRECTED);
        cout << "Read an edge: " << strtol(out[0].c_str(), NULL, 0) << ", " << strtol(out[1].c_str(), NULL, 0) << ", "
             << strtol(out[2].c_str(), NULL, 0)
             << endl;
    }

    gv->rearrange();
}

int main() {
    //exercise1();
    exercise2();
    //exercise3();

    getchar();
    return 0;
}
