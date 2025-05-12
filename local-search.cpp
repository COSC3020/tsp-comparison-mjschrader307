#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to calculate the distance between two cities
double distance(pair<double, double> city1, pair<double, double> city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

// Function to calculate the total distance of a tour
double tour_distance(const vector<int>& tour, const vector<pair<double, double>>& cities) {
    double total_distance = 0.0;
    int n = tour.size();
    for (int i = 0; i < n - 1; ++i) {
        total_distance += distance(cities[tour[i]], cities[tour[i + 1]]);
    }
    total_distance += distance(cities[tour[n - 1]], cities[tour[0]]); // Return to the starting city
    return total_distance;
}

// 2-opt swap function
void two_opt_swap(vector<int>& tour, int i, int k) {
    reverse(tour.begin() + i + 1, tour.begin() + k + 1);
}

// 2-opt local search algorithm
vector<int> two_opt(vector<int> initial_tour, const vector<pair<double, double>>& cities) {
    vector<int> best_tour = initial_tour;
    double best_distance = tour_distance(initial_tour, cities);
    int n = cities.size();
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; ++i) {
            for (int k = i + 1; k < n; ++k) {
                vector<int> new_tour = best_tour;
                two_opt_swap(new_tour, i, k);
                double new_distance = tour_distance(new_tour, cities);

                if (new_distance < best_distance) {
                    best_distance = new_distance;
                    best_tour = new_tour;
                    improved = true;
                }
            }
        }
    }
    return best_tour;
}

// Function to generate random cities
vector<pair<double, double>> generate_random_cities(int n) {
    vector<pair<double, double>> cities;
    for (int i = 0; i < n; ++i) {
        cities.push_back({(rand() % 100) / 10.0, (rand() % 100) / 10.0}); // Random x, y between 0 and 10
    }
    return cities;
}

int main() {
    srand(time(0)); // Seed the random number generator
    vector<int> n_values = {200}; // Sizes of n

    for (int n : n_values) {
        cout << "Running 2-opt for n = " << n << " cities:" << endl;

        // Generate random cities
        vector<pair<double, double>> cities = generate_random_cities(n);

        // Create initial tour
        vector<int> initial_tour(n);
        for (int i = 0; i < n; ++i) {
            initial_tour[i] = i;
        }

        // Start timing
        auto start = high_resolution_clock::now();

        // Run 2-opt
        vector<int> optimized_tour = two_opt(initial_tour, cities);

        // Stop timing
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        // Output results
        cout << "Optimized Tour: ";
        for (int city_index : optimized_tour) {
            cout << city_index << " ";
        }
        cout << endl;
        cout << "Optimized Distance: " << tour_distance(optimized_tour, cities) << endl;
        cout << "Time Taken: " << duration.count() << " ms" << endl;
        cout << "-----------------------------" << endl;
    }

    return 0;
}
