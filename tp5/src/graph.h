/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "mutable_priority_queue.h"

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template<class T>
class Vertex {
    T info;                        // content of the vertex
    vector<Edge<T>> adj;        // outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0;        // required by MutablePriorityQueue

    bool visited = false;        // auxiliary field
    bool processing = false;    // auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);

    T getInfo() const;

    double getDist() const;

    Vertex *getPath() const;

    bool operator<(Vertex<T> &vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;

    friend class MutablePriorityQueue<Vertex<T>>;
};


template<class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const {
    return this->dist < vertex.dist;
}

template<class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template<class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template<class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
    Vertex<T> *dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);

    friend class Graph<T>;

    friend class Vertex<T>;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    // Floyd Warshall required containers and functions
    double **distance;
    int **next;

    int getIndexOf(const T &info) const;

public:
    ~Graph();

    Vertex<T> *findVertex(const T &in) const;

    bool addVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w);

    int getNumVertex() const;

    vector<Vertex<T> *> getVertexSet() const;

    // Fp05 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    vector<T> getPathTo(const T &dest) const;   //TODO...

    // Fp05 - all pairs
    void floydWarshallShortestPath();   //TODO...
    vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template<class T>
Graph<T>::~Graph() {
    /*if (distance != NULL) {
        for (int i = 0; i < vertexSet.size(); ++i) {
            if (distance[i] != NULL)
                delete[] distance[i];

        }

        delete[] distance;
    }

    if (next != NULL) {
        for (int i = 0; i < vertexSet.size(); ++i) {
            if (next[i] != NULL)
                delete[] next[i];

        }

        delete[] next;
    }*/
}

template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    Vertex<T> *source = findVertex(orig);

    if (!source) return;

    for (Vertex<T> *v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }

    queue<Vertex<T> *> tmp_queue;

    tmp_queue.push(source);

    source->dist = 0;

    while (!tmp_queue.empty()) {
        Vertex<T> *current = tmp_queue.front();

        for (Edge<T> &edge : current->adj) {
            if (edge.dest->dist == INF) {
                edge.dest->dist = current->dist + 1;
                edge.dest->path = current;
                tmp_queue.push(edge.dest);
            }
        }

        tmp_queue.pop();
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &orig) {
    Vertex<T> *source = findVertex(orig);

    if (!source) return;

    for (Vertex<T> *v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }

    MutablePriorityQueue<Vertex<T>> tmp_queue;

    tmp_queue.insert(source);

    source->dist = 0;

    while (!tmp_queue.empty()) {
        Vertex<T> *current = tmp_queue.extractMin();

        for (Edge<T> &edge : current->adj) {
            if (edge.dest->dist > current->dist + edge.weight) {
                double old_dist = edge.dest->dist;
                edge.dest->dist = current->dist + edge.weight;
                edge.dest->path = current;

                if (old_dist == INF)
                    tmp_queue.insert(edge.dest);
                else
                    tmp_queue.decreaseKey(edge.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    Vertex<T> *source = findVertex(orig);

    if (!source) return;

    for (Vertex<T> *v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }

    source->dist = 0;

    for (int i = 1; i < vertexSet.size(); ++i)
        for (Vertex<T> *v : vertexSet)
            for (Edge<T> &edge : v->adj) {
                if (edge.dest->dist > v->dist + edge.weight) {
                    edge.dest->dist = v->dist + edge.weight;
                    edge.dest->path = v;
                }
            }

    for (Vertex<T> *v : vertexSet)
        for (Edge<T> &edge : v->adj)
            if (v->dist + edge.weight < edge.dest->dist )
                cout << "There are negative cycles!" << endl;

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const {
    vector<T> res;

    stack<T> tmp;

    Vertex<T> *current = findVertex(dest);

    while (current != NULL) {
        tmp.push(current->getInfo());

        current = current->getPath();
    }

    while (!tmp.empty()) {
        res.push_back(tmp.top());

        tmp.pop();
    }

    return res;
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
int Graph<T>::getIndexOf(const T &info) const {
    for (int i = 0; i < vertexSet.size(); ++i)
        if (vertexSet[i]->info == info) return i;

    return -1;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    distance = new double *[vertexSet.size()];
    next = new int *[vertexSet.size()];

    for (int i = 0; i < vertexSet.size(); ++i) {
        distance[i] = new double[vertexSet.size()];
        next[i] = new int[vertexSet.size()];

        for (int j = 0; j < vertexSet.size(); ++j) {
            distance[i][j] = j == i ? 0 : INF;
            next[i][j] = -1;
        }

        for (Edge<T> &edge : vertexSet[i]->adj) {
            int destIndex = getIndexOf(edge.dest->info);

            distance[i][destIndex] = edge.weight;
            next[i][destIndex] = destIndex;
        }
    }

    for (int k = 0; k < vertexSet.size(); ++k) {
        for (int i = 0; i < vertexSet.size(); ++i) {
            for (int j = 0; j < vertexSet.size(); ++j) {
                // Because of the use of infinity the sum below can throw an overflow
                if (distance[i][k] == INF || distance[k][j] == INF) continue;

                double potentialDistance = distance[i][k] + distance[k][j];
                if (distance[i][j] > potentialDistance) {
                    distance[i][j] = potentialDistance;
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const {
    vector<T> res;

    int start = getIndexOf(orig);
    int end = getIndexOf(dest);

    if (distance[start][dest] == INF) return res;

    int current = start;
    for (; current != end; current = next[current][end])
        if (current == -1) return vector<T>();
        else res.push_back(vertexSet[current]->info);

    if (next[current][dest] == -1) return vector<T>();
    res.push_back(vertexSet[current]->info);
    return res;
}

#endif /* GRAPH_H_ */
