#include <fstream>
#include <iostream>
#include <sstream>
#include "Campus.h"

using namespace std;

/* Constructor that opens the file for the locations and distances,
 * and builds the adjacency list, node list, and map.
 */
Campus::Campus(string name) {
    /* The filename should be in the 
     * format (name of the campus).txt
     */
    string campusFile = name + ".txt";
    ifstream file(campusFile);

    // Check for error opening file.
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    unordered_map<string, int> map;
    vector<vector<Edge>> list;
    vector<Node> locations;
    string line, source, destination;
    int distance;

    while(getline(file, line)) {
        stringstream ss(line);

        /* Parse the data in the format "Source-Destination:Distance" */
        getline(ss, source, '-');
        getline(ss, destination, ':');
        ss >> distance;

        /* If the source node does not yet exist in the map, add it. */
        if (map.find(source) == map.end()) {
            map[source] = locations.size();
            locations.push_back(Node(source));
        }
        
        /* If the destination node does not exist in the map, add it. */
        if (map.find(destination) == map.end()) {
            map[destination] = locations.size();
            locations.push_back(Node(destination));
        }

        /* Resize the adjacency list according to the number of new
         * nodes we read from the file. Then build the adjacency list,
         * pushing back the source and the node that it is connected to.
         * Since this is an undirected graph, we need to store the 
         * destination back to the source node.
         */
        list.resize(locations.size());
        list[map[source]].push_back(Edge(destination, distance));
        list[map[destination]].push_back(Edge(source, distance));
    }    

    this->adjList = list;
    this->nodes = locations;
    this->nodeIndexMap = map;

    file.close();
}

/* returns the index map of this campus. */
unordered_map<string, int> Campus::getNodeIndexMap() {
    return nodeIndexMap;
}

/* Returns the adjacency list of this campus. */
vector<vector<Edge>> Campus::getAdjList() {
    return adjList;
}

/* Returns the list of locations of this campus. */
vector<Node> Campus::getNodes() {
    return nodes;
}

/* Returns the name of this campus. */
string Campus::getCampusName() {
    return campusName;
}





























