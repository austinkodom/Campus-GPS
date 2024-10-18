//----------------------------------------------------------------------------
// Name: Austin Odom, Austin Davis, DJ Odle
// Course: CS-355
// Assignment: Group Project #3
// Due Date: 11/19/23
// This is our main file which makes use of everything we have created
// to show the shortest path from point A to point B. This also includes our
// most important function which is Dijkstra's Algorithm.
//----------------------------------------------------------------------------
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Campus.h"
#include "Edge.h"
#include "Node.h"

using namespace std;

string getSelection(Campus*, string, bool);
void performDijkstrasAlgorithm(Campus*, string, string);
void displayPath(vector<string>, int);

//---------------------------------------------------------------------------------------------------
// MAIN FUNCTION
// The main function orchestrates the interaction with the user to find paths
// between locations in a school environment using Dijkstra's algorithm.
// The program iteratively prompts the user for starting and ending locations,
// calculates the shortest path, and displays the result.
//
// PROGRAM FLOW:
// 1. Initialize the school and obtain the adjacency list representing the school map.
// 2. Iterate the program as long as the user wants to continue finding paths.
//    a. Get the list of available locations from the school map.
//    b. Map node names to indices for efficient lookup.
//    c. Prompt the user for the starting location using getUserChoice function.
//    d. Prompt the user for the ending location using getUserChoice function.
//    e. Perform Dijkstra's algorithm with the selected starting point to find the shortest path.
//    f. Display the path and distances between locations using the displayPath function.
//    g. Ask the user if they want to continue finding paths.
// 3. Return 0 to indicate successful program completion.
//---------------------------------------------------------------------------------------------------
int main() {
	Campus* campus;
	bool flag = true;
	
	campus = new Campus("UNA");
	
	while (flag) {
		/* Get the starting and ending point from the user. */
		string start = getSelection(campus, "Enter Starting Location: ", false);
		string end = getSelection(campus, "Enter Ending Location: ", true);
		
		performDijkstrasAlgorithm(campus, start, end);
		
		/* Ask the user to continue. */
		cout << "Do you want to find another route? (1 to continue, any key to exit): ";
		int choice;
		cin >> choice;
		
		if (choice != 1)
			flag = false;
		
		// Consume the newline character left in the input buffer.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	// Clean up dynamically allocated campus object.
	delete campus;

	return 0;
}

//---------------------------------------------------------------------------------------------
// Perform Dijkstra's algorithm on a graph represented by an adjacency list.
// INCOMING DATA:
// - Campus Object: Used to grab the adjacency list, index map, and node list associated.
// - start: Starting node for the algorithm.
// - end: Ending node
// OUTGOING DATA: Printed path and total distance of the path.
// RETURN: NONE
//---------------------------------------------------------------------------------------------
void performDijkstrasAlgorithm(Campus* campus, string start, string end) {
	vector<vector<Edge>> adjList = campus->getAdjList();
	vector<Node> nodes = campus->getNodes();
	unordered_map<string, int> nodeIndexMap = campus->getNodeIndexMap();
	
	vector<float> currentDistance(nodes.size(), numeric_limits<float>::infinity());		
	vector<bool> toBeChecked(nodes.size(), true);
	vector<string> path;  			                                                                                              
	vector<Node> predecessor(nodes.size(), Node("")); 
	
	// Use a priority queue to efficiently retrieve the node with the minimum distance.
	using queElement = pair<float, int>;
	priority_queue<queElement, vector<queElement>, greater<queElement>> pq;
				
	int first = nodeIndexMap[start];  
	int last = nodeIndexMap[end];
	
	int totalDistance = 0;
	currentDistance[first] = 0;
	pq.push({0, first});	// Push the starting node with distance zero.
	
	while (!pq.empty()) {
		// Extract the node with the minimum distance.
		int v = pq.top().second;
		pq.pop();
		
		// Skip the node if it has already been checked.
		if (!toBeChecked[v]) continue;
		toBeChecked[v] = false;		
		
		// Explore the neighbors of the current node.
		for (const auto& edge : adjList[v]) {
			int u = nodeIndexMap[edge.destination];
			int weight = edge.distance;
			
			// If a shorter path is found, update the distance and predecessor.
			if (currentDistance[u] > currentDistance[v] + weight) {
				currentDistance[u] = currentDistance[v] + weight;
				predecessor[u] = nodes[v];	
				
				// Push the updated distance and node to priority queue.
				pq.push({currentDistance[u], u});
			}
		}
	}
	
	// Backtrack through the predecessor vector to find the full path steps.
	Node current = nodes[last];
	while (current.name != "") {
		path.push_back(current.name);
		current = predecessor[nodeIndexMap[current.name]];
	}
	
	totalDistance = currentDistance[last];
	
	displayPath(path, totalDistance);
}

//--------------------------------------------------------------------------------------------
// Get and validate the user's choice from a list of locations.
// INCOMING DATA:
// - Campus Object: To get the available locations.
// - prompt: Prompt message for the user.
// - endingChoice: Boolean flag indicating whether it's an ending choice (default is false).
// OUTGOING DATA: Displayed output to the console.
// RETURN: Chosen location.
//--------------------------------------------------------------------------------------------
string getSelection(Campus* campus, string prompt, bool endingChoice) {
	vector<Node> locations;
	int choice;
	
	locations = campus->getNodes();
	// Display available locations if it's not an ending choice.
	if (!endingChoice) {
		cout << "Available Locations: " << endl;
		
		for (size_t i = 0; i < locations.size(); i++) {
			cout << i + 1 << ". " << locations[i].name << endl;
		}
	}
	
	// Prompt for user input
	cout << prompt;
	cin >> choice;
	
	// Validate the user's choice.
	while (choice < 1 || static_cast<size_t>(choice) > locations.size()) {
		// Display error message for invalid choice.
		cerr << "Invalid choice. Please try again." << endl;
		cout << prompt;
		
		// Clear the fail state of cin.
		cin.clear();
		
		// Ignore any invalid input in the buffer.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
	}
	
	// Return the chosen selection.
	string chosenLocation = locations[choice - 1].name;
	return chosenLocation;
}

//------------------------------------------------------------------------------------
// Display the steps and distances to get from the start node to the end node.
// INCOMING DATA:
// - path: Vector representing the shortest path from the start node to the end node.
// - distance: Total distance of the path.
// OUTGOING DATA: Displayed output to the console.
// RETURN: NONE
//------------------------------------------------------------------------------------
void displayPath(vector<string> path, int distance) {
	cout << "\nShortest Path from " << path.back() << " to " << path.front() << endl;
	
	for (int i = path.size() - 1; i >= 0; i--) {
		cout << path[i];
		
		if (i > 0)
			cout << " -> ";
	
	}
	
	cout << "\nTotal Distance: " << distance << endl;
}
















