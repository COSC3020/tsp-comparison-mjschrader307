// COMPUTER GEEK – compgeek.co.in
// Write a program for Held-Karp Algorithm

#include <iostream>
#include <limits.h>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

const int INF = INT_MAX / 2;

// Function to find the minimum of two values
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to solve the TSP using the Held-Karp algorithm
// Modified to use dynamically allocated arrays
int tsp(int n, vector<vector<int>>& dist) {
    // Total number of subsets (2^n)
    int totalSubsets = 1 << n;

    // DP table to store the minimum cost of visiting a subset of cities and ending at a specific city
    // Use vector for dynamic allocation
    vector<vector<int>> dp(totalSubsets, vector<int>(n, INF));

    // Starting point, cost is 0 to start from the first city
    dp[1][0] = 0;

    // Iterate over all subsets of cities
    for (int mask = 1; mask < totalSubsets; mask++) {
        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) {
                for (int v = 0; v < n; v++) {
                    if ((mask & (1 << v)) == 0) {
                        int newMask = mask | (1 << v);
                        dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
                    }
                }
            }
        }
    }

    // Find the minimum cost to complete the tour
    int minCost = INF;
    for (int i = 1; i < n; i++) {
        minCost = min(minCost, dp[totalSubsets - 1][i] + dist[i][0]);
    }

    return minCost;
}

// Function to generate a random distance matrix
vector<vector<int>> generateDistanceMatrix(int n) {
    // Create a vector of vectors with size n x n
    vector<vector<int>> dist(n, vector<int>(n, 0));
    
    // Use a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);  // Random distances between 1 and 100
    
    // Fill the distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;  // Distance to self is 0
            } else {
                dist[i][j] = distrib(gen);
            }
        }
    }
    
    return dist;
}

int main() {
    // Array of test sizes
    vector<int> testSizes = {26};
    double lastDuration = 0.0;
    
    cout << "Testing Held-Karp algorithm with different input sizes:" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << setw(5) << "Size" << setw(15) << "Duration (s)" << setw(15) << "Growth Ratio" << setw(15) << "Min Cost" << endl;
    cout << "-----------------------------------------------------" << endl;
    
    for (size_t i = 0; i < testSizes.size(); i++) {
        int n = testSizes[i];
        
        // Create distance matrix (dynamically sized)
        vector<vector<int>> dist = generateDistanceMatrix(n);
        
        // Start timing
        auto start = chrono::high_resolution_clock::now();
        
        // Run the algorithm
        int result = tsp(n, dist);
        
        // End timing
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        
        // Calculate growth ratio if not the first test
        double ratio = 0.0;
        if (i > 0 && lastDuration > 0) {
            ratio = duration.count() / lastDuration;
        }
        
        // Print results
        cout << setw(5) << n 
             << setw(15) << fixed << setprecision(6) << duration.count();
        
        if (ratio > 0) {
            cout << setw(15) << fixed << setprecision(2) << ratio << "x";
        } else {
            cout << setw(15) << "-";
        }
        
        cout << setw(15) << result << endl;
        
        // Save duration for next iteration's ratio calculation
        lastDuration = duration.count();
        
        // If duration is already more than 30 seconds, estimate larger sizes
        if (duration.count() > 30) {
            cout << "\nTest for n = " << n << " took over 30 seconds." << endl;
            cout << "Estimated time for n = " << n+1 << ": " << duration.count() * 2.1 << "s" << endl;
            cout << "Estimated time for n = " << n+2 << ": " << duration.count() * 4.4 << "s" << endl;
            
            // Estimate time for 1-hour runtime
            double base = duration.count();
            int estimatedN = n;
            double estimatedTime = base;
            
            while (estimatedTime < 3600) { // 3600 seconds = 1 hour
                estimatedN++;
                estimatedTime *= 2.1; // Conservative growth estimate
            }
            
            break;
        }
    }
    
    return 0;
}