#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int INF = numeric_limits<int>::max();

void floydWarshallParallel(vector<vector<int>>& graph, int numVertices) {
    #pragma omp parallel for
    for (int k = 0; k < numVertices; ++k) {
        #pragma omp parallel for
        for (int i = 0; i < numVertices; ++i) {
            #pragma omp parallel for
            for (int j = 0; j < numVertices; ++j) {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][k] + graph[k][j] < graph[i][j]) {
                    #pragma omp critical
                    {
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    const int numVertices = 4;

    // Example graph with weighted edges
    vector<vector<int>> graph = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    // Measuring parallel execution time
    auto start = high_resolution_clock::now();

    // Applying the parallel Floyd-Warshall algorithm
    floydWarshallParallel(graph, numVertices);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Printing the shortest paths
    cout << "Shortest Paths:\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (graph[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << graph[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "Parallel Execution Time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
