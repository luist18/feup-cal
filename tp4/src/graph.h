#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;

/****************** Provided structures  ********************/

template<class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field used by dfs and bfs
    int indegree;          // auxiliary field used by topsort
    bool processing;       // auxiliary field used by isDAG

    void addEdge(Vertex<T> *dest, double w);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);

    friend class Graph<T>;
};

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
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

    Vertex<T> *findVertex(const T &in) const;

    bool dfsIsDAG(Vertex<T> *v) const;

public:
    int getNumVertex() const;

    bool addVertex(const T &in);

    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w);

    bool removeEdge(const T &sourc, const T &dest);

    vector<T> dfs() const;

    vector<T> bfs(const T &source) const;

    vector<T> topsort() const;

    int maxNewChildren(const T &source, T &inf) const;

    bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in) {}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL) return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> *source = findVertex(sourc);
    Vertex<T> *destination = findVertex(dest);
    if (source == NULL || destination == NULL) return false;
    source->addEdge(destination, w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *source = findVertex(sourc);
    Vertex<T> *destination = findVertex(dest);
    if (source == NULL || destination == NULL) return false;
    return source->removeEdgeTo(destination);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    auto it = find_if(adj.begin(), adj.end(), [&d](const Edge<T> edge) {
        return edge.dest == d;
    });
    if (it == adj.end()) return false;
    adj.erase(it);
    return true;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template<class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T> *source = findVertex(in);
    if (source == NULL) return false;

    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it) {
        (*it)->removeEdgeTo(source);
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it) {
        if ((*it) == source) {
            vertexSet.erase(it);
            break;
        }
    }

    delete source;

    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
    // TODO (10 lines)
    for (Vertex<T> *v : vertexSet)
        v->visited = false;

    vector<T> res;

    for (Vertex<T> *v : vertexSet) {
        if (!v->visited)
            dfsVisit(v, res);
    }

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    // TODO (7 lines)
    v->visited = true;
    res.push_back(v->info);
    for (Edge<T> e : v->adj)
        if (!e.dest->visited)
            dfsVisit(e.dest, res);
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::bfs(const T &source) const {
    // TODO (22 lines)
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    Vertex<T> *starter = findVertex(source);

    for (Vertex<T> *v : vertexSet)
        v->visited = false;

    vector<T> res;
    queue<Vertex<T> *> tmp_queue;

    tmp_queue.push(starter);
    starter->visited = true;

    while (!tmp_queue.empty()) {
        Vertex<T> *current = tmp_queue.front();

        res.push_back(current->info);

        for (Edge<T> edge : current->adj) {
            if (!edge.dest->visited) {
                tmp_queue.push(edge.dest);
                edge.dest->visited = true;
            }
        }

        tmp_queue.pop();
    }

    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
    // TODO (26 lines)
    vector<T> res;

    for (Vertex<T> *vertex : vertexSet) {
        vertex->indegree = 0;
    }

    for (Vertex<T> *vertex : vertexSet) {
        for (Edge<T> &edge : vertex->adj)
            edge.dest->indegree++;
    }

    queue<Vertex<T> *> tmp_queue;

    for (Vertex<T> *vertex : vertexSet) {
        if (!vertex->indegree)
            tmp_queue.push(vertex);
    }

    while (!tmp_queue.empty()) {
        Vertex<T> *current = tmp_queue.front();

        res.push_back(current->info);

        for (Edge<T> &edge : current->adj) {
            edge.dest->indegree--;

            if (!edge.dest->indegree)
                tmp_queue.push(edge.dest);
        }

        tmp_queue.pop();
    }

    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template<class T>
int Graph<T>::maxNewChildren(const T &source, T &inf) const {
    int res = 0;
    // 1. Breadth first search.
    // The pos-processing is calculating the out-degree, which is the size of the edges vector.
    Vertex<T> *starter = findVertex(source);

    for (Vertex<T> *v : vertexSet)
        v->visited = false;

    queue<Vertex<T> *> tmp_queue;
    tmp_queue.push(starter);
    starter->visited = true;

    while (!tmp_queue.empty()) {
        Vertex<T> *current = tmp_queue.front();

        int count = 0;

        for (Edge<T> edge : current->adj) {
            if (!edge.dest->visited) {
                count++;
                tmp_queue.push(edge.dest);
                edge.dest->visited = true;
            }
        }

        if (count > res) {
            res = count;
            inf = current->info;
        }

        tmp_queue.pop();
    }

    return res;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template<class T>
bool Graph<T>::isDAG() const {
    for (Vertex<T> *v : vertexSet)
        v->visited = false;

    for (Vertex<T> *v : vertexSet) {
        if (!v->visited) {
            for (Vertex<T> *g: vertexSet)
                g->processing = false;

            if (!dfsIsDAG(v))
                return false;
        }
    }

    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;

    for (Edge<T> e : v->adj)
        if (e.dest->processing)
            return false;
        else if (!dfsIsDAG(e.dest))
                return false;
        else
            e.dest->processing = false;

    return true;
}

#endif /* GRAPH_H_ */
