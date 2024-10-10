/*
 * Program: Graph Traversal Using BFS (Assignment #1)
 * Name: Mariam Merza
 * ID: 0763480
 * Date Created: 10/08/2024
 * Last Modified: 10/10/2024
*/

#include <iostream>      // For input/output services
#include <vector>        // For storing multiple parents for each node if multiple shortest paths exist
#include <queue>         // For the BFS algorithm, which uses a queue data structure
#include <unordered_map> // For storing elements formed by a key value and a mapped value
#include <unordered_set> // For storing keys in any order

using namespace std;

// Define the adjacent vertices using an unordered map called 'Adj'
// Each key represents a vertex in the graph, and its corresponding value is a vector of adjacent vertices
unordered_map<char, vector<char>> Adj = {
    {'a', {'b', 's'}},                // Vertex a has adjacent vertices {b, s}
    {'b', {'a', 'c'}},                // Vertex b has adjacent vertices {a, c}
    {'c', {'b', 'd', 's'}},           // Vertex c has adjacent vertices {b, d, s}
    {'d', {'c', 'f', 'g', 's'}},      // Vertex d has adjacent vertices {c, f, g, s}
    {'e', {'f', 'g', 's'}},           // Vertex e has adjacent vertices {f, g, s}
    {'f', {'d', 'e', 'g'}},           // Vertex f has adjacent vertoces {d, e, g}
    {'g', {'d', 'e', 'f'}},           // Vertex g has adjacent vertices {d, e, f}
    {'s', {'a', 'c', 'd', 'e'}}       // Vertex s has adjacent vertices {a, c, d, e}
};

// Function to perform BFS and gather parent information, based on the pseudocode example from class
void bfs(char start, char goal, unordered_map<char, vector<char>>& parents) {
    unordered_map<char, int> level;   // Create a map to store the level of each vertex
    queue<char> q;                    // Create a queue for storing vertices to be processed

    level[start] = 0;  // Initialize the level of the starting vertex to 0
    q.push(start);     // Add the starting vertex to the queue

    while (!q.empty()) {         // While the queue is not empty...
        char u = q.front();      // Retrieve the first element of the queue and return a reference to it
        q.pop();                 // Remove the element at the front of the queue

        // Process each adjacent vertex of 'u'
        for (char v : Adj[u]) {
            if (level.find(v) == level.end()) {    // If 'v' has not been visited yet
                level[v] = level[u] + 1;           // Set the level of 'v' to the level of 'u' + 1
                parents[v].push_back(u);           // Add 'u' as a parent of 'v'
                q.push(v);                         // Add 'v' to the queue
            }
            else if (level[v] == level[u] + 1) {   // If we find another shortest path to 'v'
                parents[v].push_back(u);           // Add another parent
            }
        }
    }
}

// Recursive function to reconstruct all paths from 'goal' to 'start'
void findPaths(char current, char start, unordered_map<char, vector<char>>& parents, vector<char>& path, vector<vector<char>>& allPaths) {
    if (current == start) {
        path.push_back(start);                   // Add the starting vertex to the path
        reverse(path.begin(), path.end());       // Reverse the path to get the correct order
        allPaths.push_back(path);                // Add the path to the list of all paths
        reverse(path.begin(), path.end());       // Reverse the path again to restore its original order
        path.pop_back();                         // Remove the starting vertex from the path
        return;
    }

    path.push_back(current);                                // Add the current vertex to the path
    for (char parent : parents[current]) {                  // Process each parent of the current vertex
        findPaths(parent, start, parents, path, allPaths);  // Recursively find paths from the parent vertex to the start vertex
    }
    path.pop_back();    // Remove the current vertex from the path
}

int main() {
    char start, goal;
    cout << "Enter the starting vertex: ";
    cin >> start;
    cout << "Enter the ending vertex: ";
    cin >> goal;

    // To store parent nodes for each vertex
    unordered_map<char, vector<char>> parents;
    bfs(start, goal, parents);

    // If no path exists to the goal
    if (parents.find(goal) == parents.end()) {
        cout << "No path from " << start << " to " << goal << endl;
    }
    else {
        vector<vector<char>> allPaths;
        vector<char> path;

        // Find all paths from goal to start
        findPaths(goal, start, parents, path, allPaths);

        cout << "Shortest path from vertex " << start << " to vertex " << goal << " is:" << endl;

        // Print all paths, separated by " or "
        for (size_t i = 0; i < allPaths.size(); ++i) {
            const auto& p = allPaths[i];

            // Print the path
            for (size_t j = 0; j < p.size(); ++j) {
                cout << p[j];
                if (j != p.size() - 1) {
                    cout << " --> ";
                }
            }

            // Add " or " if it's not the last path
            if (i != allPaths.size() - 1) {
                cout << " or ";
            }
        }
        cout << endl;
    }

    return 0;
}