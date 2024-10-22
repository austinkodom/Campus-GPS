#ifndef EDGE_H
#define EDGE_H

#include <string>
using namespace std;

/* A struct Edge acting as the connection between
 * nodes (vertices, or locations). Each connection
 * contains a weighted distance and the destination
 * node.
 */
struct Edge {
    string destination;
    int distance;

    Edge(const string& dest, int dist) : destination(dest), distance(dist) {}
};

#endif // EDGE_H
