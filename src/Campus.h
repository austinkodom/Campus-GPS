#ifndef CAMPUS_H
#define CAMPUS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Edge.h"
#include "Node.h"

using namespace std;

/* Campus class that will store the name of the campus,
 * an adjacency list for each node and all of its edges,
 * a node list for all available locations on campus,
 * and an unordered_map that will give nodes an index
 * value, that will help perform Dijkstra's algorithm.
 */
class Campus {
    private: 
        unordered_map<string , int> nodeIndexMap;
        vector<vector<Edge>>    adjList;
        vector<Node> nodes;
        string campusName;

    public:
        Campus(string);
        unordered_map<string, int> getNodeIndexMap();
        vector<vector<Edge>> getAdjList();
        vector<Node> getNodes();
        string getCampusName();
};

#endif //CAMPUS_H
