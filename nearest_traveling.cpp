
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

// Start of the code

const int N = 10;  // N is the number of lines from the graph file
int graph[N][N];   // graph is a 2D array to store the graph from the file

int minCost = INT_MAX; // minCost is the minimum cost of traveling, set to the maximum integer value
vector<int> bestPath;  // bestPath is the best Hamiltonian cycle path


/**
 * @brief This function traverses the graph using the nearest neighbor algorithm
 * by starting from the first city and visiting the next nearest city
 */
void nearestNeighbor() {

    // Create a vector to store the visited cities
    vector<bool> visited(N, false);
    vector<int> path;

    path.push_back(0); 
    visited[0] = true;


    int current = 0;
    int totalCost = 0;

    // Visit the next nearest city until all the cities are visited
    for (int count = 0; count < N - 1; ++count) {
        int next = -1;
        int minDistance = INT_MAX;

        for (int i = 0; i < N; ++i) {
            if (!visited[i] && graph[current][i] < minDistance) {
                minDistance = graph[current][i];
                next = i;
            }
        }

        if (next != -1) {
            path.push_back(next);
            visited[next] = true;
            totalCost += minDistance;
            current = next;
        }
    }

    // Add the cost of traveling from the last city to the starting city
    totalCost += graph[current][0];
    path.push_back(0);

    if (totalCost < minCost) {
        minCost = totalCost;
        bestPath = path;
    }
}

int main() {

    
    auto start = chrono::high_resolution_clock::now();
    
    // Read from the given graph file
    ifstream file("Size10.graph");
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            file >> graph[i][j];
            if (i != j) 
                graph[j][i] = graph[i][j];
        }
    }


    file.close();

    // Call the nearestNeighbor function
    nearestNeighbor();

    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    //Print out
    cout << "Best Hamiltonian Cycle Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Minimum cost of traveling: " << minCost << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}
