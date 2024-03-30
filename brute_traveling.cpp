/**
 * @file brute_traveling.cpp
 * @author Jeongbin Son
 * @brief CS470, Project 1, Brute Force Implementation of Traveling Salesman Problem
 * @date 2024-02-22
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>
#include <chrono>

using namespace std;

// Start of the code

const int N = 10;  // N is the number of lines from the graph file
int graph[N][N];   // graph is a 2D array to store the graph from the file

int minCost = INT_MAX; // minCost is the minimum cost of traveling, set to the maximum integer value
vector<int> bestPath;  // bestPath is the best Hamiltonian cycle path


/**
 * @brief This function is a recursive function to find the best Hamiltonian cycle path
 * by using the brute force method: trying all the possible paths
 */
void tsp(vector<int>& path, vector<bool>& visited, int cost, int current) {
    // If the path size is equal to N, then we have visited all the cities
    // We need to add the cost of traveling from the last city to the starting city
    if (path.size() == N) { 
        if (cost + graph[current][0] < minCost) {
            minCost = cost + graph[current][0]; 
            bestPath = path;
        }
        return;
    }
    // If the path size is less than N, then we have not visited all the cities
    // We need to visit all the cities and find the best Hamiltonian cycle path
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            tsp(path, visited, cost + graph[current][i], i); 
            path.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    // Start the timer to measure the time taken to find the best Hamiltonian cycle path
    auto start = chrono::high_resolution_clock::now();
    
    // Read from the given graph file
    ifstream file("Size10.graph");
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Store the graph from the file to the 2D array
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            file >> graph[i][j];
            if (i != j) 
                graph[j][i] = graph[i][j];
        }
    }
    file.close();


    // Initialize the path and visited vectors
    vector<int> path;
    vector<bool> visited(N, false);

    path.push_back(0); 
    visited[0] = true;


    //Call the recursive function to find the best Hamiltonian cycle path
    tsp(path, visited, 0, 0);

    // Stop the timer that we started earlier
    auto end = chrono::high_resolution_clock::now();

    // Calculate the time taken to find the best Hamiltonian cycle path
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);


    //Print out
    cout << "Minimum cost of traveling: " << minCost << endl;
    cout << "Best Hamiltonian Cycle Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << "0" << endl; 

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}
