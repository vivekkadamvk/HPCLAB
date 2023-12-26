#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <omp.h>

using namespace std;

struct Point {
    double x, y;
    int label;
};

double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int simpleParallelKNN(const vector<Point>& dataset, const Point& query, int k) {
    int n = dataset.size();
    vector<int> counts(2, 0); // Assuming binary classification (labels 1 and 2)

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double distance = euclideanDistance(dataset[i], query);
        
        #pragma omp critical
        {
            if (distance < numeric_limits<double>::infinity()) {
                int label = dataset[i].label;
                #pragma omp atomic
                counts[label - 1]++;
            }
        }
    }

    // Return the label with the majority of neighbors
    return (counts[0] > counts[1]) ? 1 : 2;
}

int main() {
    // Example dataset
    vector<Point> dataset = {
        {1.0, 2.0, 1},
        {2.0, 3.0, 1},
        {3.0, 4.0, 2},
        {4.0, 5.0, 2}
        // Add more points as needed
    };

    // Example query point
    Point query = {2.5, 3.5, 0};  // The label is unknown for the query point

    // Set the number of neighbors (k)
    int k = 3;

    // Perform parallel k-NN classification
    int predictedLabel = simpleParallelKNN(dataset, query, k);

    cout << "Predicted Label for the Query Point: " << predictedLabel << endl;

    return 0;
}
