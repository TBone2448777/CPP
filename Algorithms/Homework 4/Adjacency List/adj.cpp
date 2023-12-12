#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_set>
#include <stack>
#include <limits>

using namespace std;

// Adds a path between two cities with corresponding weight. As is undirected it adds for both
void addEdge(map<string, vector<pair<string, int>>>& adjList, const string& u, const string& v, int weight){
    adjList[u].emplace_back(v, weight);
    adjList[v].emplace_back(u, weight);
}

// Prints adjacency list
void printAdjacencyList(const map<string, vector<pair<string, int>>>& adjList){
    // Iterates through adjList map with all strings and vectors
    for (const auto& entry : adjList) {
        // Prints the string of the map, so city name
        cout << "Adjacency list of city " << entry.first << ": ";
        // Goes through the vertex and prints city and weight
        for (const auto& neighbor : entry.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

void dfs(map<string, vector<pair<string, int>>>& adjList, const string& vertex, unordered_set<string>& visited, stack<string>& myStack){
    // For however many cities the vertex has
    for (const auto& cities : adjList.at(vertex)) {
        // Insert the city into the set and set run equal to its return. In the run variable there is a way to tell
        // if the insert was successful or not
        auto run = visited.insert(cities.first);
        // If the insert was successful
        if (run.second){
            // Add the city to the stack and print it to the console.
            myStack.push(cities.first);
            cout << ", " << cities.first;
        }
        // If insert wasn't successful we've already checked all its edges and do nothing for it with the stack
    }
    printf("\n");
}

// Depth first search call
void depthFirst(map<string, vector<pair<string, int>>>& adjList, const string& start){
    // Makes a list of visited cities and creates a stack
    unordered_set<string> visited;
    stack<string> myStack;
    // Pushes and inserts the starting city to the stack and visited
    myStack.push(start);
    visited.insert(start);
    // Prints city name to console
    cout << start;
    // While the stack isn't empty, run the inside
    while (myStack.size() > 0){
        // Get the top value of the stack and then remove it from the stack
        string currentVertex = myStack.top();
        myStack.pop();
        // Call dfs with the map, vertex from the stack, visited items, and the stacks
        dfs(adjList, currentVertex, visited, myStack);
    }
}

// Creates a city class with city one, city two, and weight
class cities{
    public:
        string cOne;
        string cTwo;
        int weight;
        cities(string cOnef, string cTwof, int weightf){
            cOne = cOnef;
            cTwo = cTwof;
            weight = weightf;
        }
};

// Adds city to cList from adjList if the pair doesn't already exist
// Because the order could change, I opted to alphabatize the values first
void cityQueuer(vector<cities>& cList, map<string, vector<pair<string, int>>>& adjList){
    // Iterates through the map
    for (const auto& entry : adjList){
        // Iterates through the different vectors within the map
        for (const auto& neighbor : entry.second) {
            // This is where it alphabetizes. Same code for both sides of this but changes dependent
            // on if they are alphabetical or backwards
            if (entry.first < neighbor.first){
                // Assumes city does not exist
                bool cityExists = false;
                // Iterates through what is already in cList
                for (const auto& existingCity : cList) {
                    // If cList has the same pair of cities
                    if (existingCity.cOne == entry.first && existingCity.cTwo == neighbor.first) {
                        // Then the pair already exists, is marked as true, and breaks out of loop
                        cityExists = true;
                        break;
                    }
                }
                // If the pair is never marked as existing, make a city class for the pair and add it to cList
                if (!cityExists){
                    cList.push_back(cities(entry.first, neighbor.first, neighbor.second));
                }
            } else {
                // Assumes city does not exist
                bool cityExists = false;
                // Iterates through what is already in cList
                for (const auto& existingCity : cList) {
                    // If cList has the same pair of cities
                    if (existingCity.cOne == neighbor.first && existingCity.cTwo == entry.first) {
                        // Then the pair already exists, is marked as true, and breaks out of loop
                        cityExists = true;
                        break;
                    }
                }
                // If the pair is never marked as existing, make a city class for the pair and add it to cList
                if (!cityExists){
                    cList.push_back(cities(neighbor.first, entry.first, neighbor.second));
                }
            }
        }
    }
}

// Prints the objects I am using as priority queues/lists
void printQueue(vector<cities>& cList){
    for (size_t i = 0; i < cList.size(); i++){
        cout << cList[i].cOne << ", " << cList[i].cTwo << " for " << cList[i].weight << "\n";
    }
}

// Gets the smallest value from cList
int getMin(vector<cities>& cList){
    // Sets minVal equal to first index
    int minVal = cList[0].weight;
    // Sets index equal to 0
    int index = 0;
    // Iterates through entire cList
    for (size_t i = 0; i < cList.size(); i++){
        // If the weight of a cList item is less than minVal, change minVal and index to match
        if (cList[i].weight < minVal){
            minVal = cList[i].weight;
            index = i;
        }
    }
    return index;
}

// Adds a particular vertex to shortestPath and track connections in clusters
void addVertex(vector<vector<string>>& clusters, vector<cities>& shortestPath, cities cities){
    // Assume city does not exist already
    bool cityExists = false;
    // Set city1 and city2 exist long so that if one city exists somewhere in clusters and the other does not,
    // then that can be properly utilized
    int city1ExistsLong = -1;
    int city2ExistsLong = -1;
    // Iterate through clusters to see if cities are already present
    for (size_t i = 0; i < clusters.size(); i++){
        // Assume cities are not currently present
        bool city1Exists = false;
        bool city2Exists = false;
        // Iterate through the different lists within clusters
        for (size_t j = 0; j < clusters[i].size(); j++){
            // If the value is equal to city one mark it as such
            // Save the index for it in the long value to later add other city to it
            if (clusters[i][j] == cities.cOne){
                city1Exists = true;
                city1ExistsLong = i;
            }
            // If the value is equal to city two mark it as such
            // Save the index for it in the long value to later add other city to it
            if (clusters[i][j] == cities.cTwo){
                city2Exists = true;
                city2ExistsLong = i;
            }
        }
        // If both cities exist in this one cluster, there is already a link between them and as such nothing
        // will happen with this particular pair. This will be reset for the next cluster scan
        if (city1Exists && city2Exists){
            cityExists = true;
        }
    }
    // If the city pair does not already exist within a cluster
    if (!cityExists){
        // If both cities exist but in two different clusters
        if (city1ExistsLong != -1 && city2ExistsLong != -1){
            // Push all of the second cluster into the first
            for (size_t i = 0; i < clusters[city2ExistsLong].size(); i++){
                clusters[city1ExistsLong].push_back(clusters[city2ExistsLong][i]);
            }
            // Erase the second cluster
            clusters.erase(clusters.begin()+city2ExistsLong);
            // Add the pair to the shortest path
            shortestPath.push_back(cities);
        // If city1 exists somewhere and city2 does not
        } else if (city1ExistsLong != -1 && city2ExistsLong == -1){
            // Add city2 to city1's cluster and add the pair to shortest path
            clusters[city1ExistsLong].push_back(cities.cTwo);
            shortestPath.push_back(cities);
        // If city2 exists somewhere and city1 does not
        } else if (city1ExistsLong == -1 && city2ExistsLong != -1){
            // Add city1 to city2's cluster and add the pair to shortest path
            clusters[city2ExistsLong].push_back(cities.cOne);
            shortestPath.push_back(cities);
        }
        // If neither city exists in any cluster yet
        else if (city1ExistsLong == -1 && city2ExistsLong == -1){
            // Create a new cluster
            vector<string> newClust;
            // Push both cities to the new cluster
            newClust.push_back(cities.cOne);
            newClust.push_back(cities.cTwo);
            // Push the new cluster to clusters
            clusters.push_back(newClust);
            // Add the pair to the shortest path
            shortestPath.push_back(cities);
        }
    }
}

// Prints out contents of clusters
void printClusters(vector<vector<string>> clusters){
    for (size_t i = 0; i < clusters.size(); i++){
        cout << "\nArray " << i << ": \n";
        for (size_t j = 0; j < clusters[i].size(); j++){
            cout << clusters[i][j] << ", ";
        }
    }
    cout << "\n\n";
}

// Performs Kruskal's algorithm to get minimum weight route between all vertices
void kruskal(map<string, vector<pair<string, int>>> adjList){
    // Sets up a cList for all paths in the algorithm no repeats
    vector<cities> cList;
    // Creates a list of cities for the shortest path at the end
    vector<cities> shortestPath;
    // Has clusters to track which cities are already connected
    vector<vector<string>> clusters;
    // Fills in the cList
    cityQueuer(cList, adjList);
    // Defines length because as the program runs, cList size changes and messes with for loop if used directly
    int len = cList.size();
    for (size_t i = 0; i < len; i++){
        // Get the index of the next smallest pair
        int index = getMin(cList);
        // Add the vertex to the shortestPath (if a connection isn't already there)
        addVertex(clusters, shortestPath, cList[index]);
        // Remove the newly added vertex to from cList
        cList.erase(cList.begin() + index);
    }
    // Show what the optimal path is
    printQueue(shortestPath);
}

int main() {
    // Create an adjacency list with different weights using strings as vertex names
    map<string, vector<pair<string, int>>> adjList;

    // Add all cities to the map with associated weights
    addEdge(adjList, "Skyfallow", "Citee", 10);
    addEdge(adjList, "Skyfallow", "Atlantis", 80);
    addEdge(adjList, "Skyfallow", "Greendale", 40);

    addEdge(adjList, "Atlantis", "Greendale", 20);
    addEdge(adjList, "Atlantis", "Eville", 60);

    addEdge(adjList, "Greendale", "Gigcity", 30);
    addEdge(adjList, "Greendale", "Loompdale", 10);

    addEdge(adjList, "Loompdale", "Gigcity", 50);
    addEdge(adjList, "Loompdale", "Eville", 90);

    // Print the adjacency list
    // printAdjacencyList(adjList);

    // Call depth first search with the city you want to start with
    // printf("\n\nDepth first traversal: ");
    // depthFirst(adjList, "Eville");
    kruskal(adjList);
    return 0;
}
