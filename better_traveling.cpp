
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <climits>
#include <random>
#include <chrono> 
#include <queue>
#include <list>
#include <set>

using namespace std;

// Start of the code

const int N = 10; // N is the number of lines from the graph file
int graph[N][N];  // graph is a 2D array to store the graph from the file


/**
 * @brief creating a struct to store the solution
 */
struct Solution {
    vector<int> path;
    int cost;

    Solution() : cost(INT_MAX) {} 
    void calculateCost() {
        cost = 0;
        for (int i = 0; i < path.size() - 1; ++i) {
            cost += graph[path[i]][path[i + 1]];
        }
        cost += graph[path.back()][path[0]]; 
    }
};

/**
 * @brief This function traverses the graph using the nearest neighbor algorithm
 */
void nearestNeighbor(Solution &solution) {
    vector<bool> visited(N, false);
    solution.path.push_back(0); 
    visited[0] = true;
    int current = 0;

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
            solution.path.push_back(next);
            visited[next] = true;
            current = next;
        }
    }

    solution.path.push_back(0); 
    solution.calculateCost();
}

/**
 * @brief This function swaps two edges in the path to find a better solution
 */
void twoOptSwap(Solution &solution) {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (int i = 0; i < N - 1; ++i) {
            for (int k = i + 1; k < N; ++k) {
                int delta = -graph[solution.path[i]][solution.path[i + 1]] - graph[solution.path[k]][solution.path[(k + 1) % N]]
                            + graph[solution.path[i]][solution.path[k]] + graph[solution.path[i + 1]][solution.path[(k + 1) % N]];
                if (delta < 0) {
                    reverse(solution.path.begin() + i + 1, solution.path.begin() + k + 1);
                    solution.calculateCost();
                    improvement = true;
                }
            }
        }
    }
}

/**
 * @brief This function uses lattice annealing to find a better solution
 */
void latticeAnnealing(Solution &solution, double startTemp, double endTemp, double coolingRate) {

    double temp = startTemp;
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    while (temp > endTemp) {
        int i = rand() % (N - 1);
        int k = (i + 1 + rand() % (N - 2)) % N; 
        if (i > k) swap(i, k); 

        int delta = -graph[solution.path[i]][solution.path[i + 1]] - graph[solution.path[k]][solution.path[(k + 1) % N]]
                    + graph[solution.path[i]][solution.path[k]] + graph[solution.path[i + 1]][solution.path[(k + 1) % N]];

        if (delta < 0 || distribution(generator) < exp(-delta / temp)) {
            reverse(solution.path.begin() + i + 1, solution.path.begin() + k + 1);
            solution.calculateCost();
        }

        temp *= coolingRate;

    }
}



int main() {
    
    auto start = chrono::high_resolution_clock::now();

    ifstream file("size10.graph");
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            file >> graph[i][j];
            if (i != j) graph[j][i] = graph[i][j];
        }
    }
    file.close();

    Solution initialSolution;
    nearestNeighbor(initialSolution);
    latticeAnnealing(initialSolution, 10000, 0.1, 0.99);
    twoOptSwap(initialSolution);
    

    
    auto end = chrono::high_resolution_clock::now();

    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Optimized path: ";
    for (int city : initialSolution.path) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Optimized cost: " << initialSolution.cost << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    

    return 0;
}
