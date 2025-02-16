#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include "chaining_table.h"
#include "linear_probing_table.h"

using namespace std;
using namespace std::chrono;

const int L = 14;
const int m = 1 << L;  // Table size: 2^L //
const int MAX_KEY = 30000;
const int EXPERIMENTS = 100;

// Generate n random keys
vector<int> generate_keys(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, MAX_KEY);

    vector<int> keys(n);
    for (int &key : keys) {
        key = dist(gen);
    }
    return keys;
}

// Measure median time // Used as a decorator
template<typename Func>
double measure_time(Func f) {
    vector<double> times;
    for (int i = 0; i < EXPERIMENTS; i++) {
        auto start = high_resolution_clock::now();
        f();  // Run the function
        auto end = high_resolution_clock::now();
        times.push_back(duration<double, micro>(end - start).count());
    }
    sort(times.begin(), times.end());  // Sort times
    return times[EXPERIMENTS / 2];  // Return median
}

int main() {
    vector<int> n_values;
    vector<double> insert_chain, insert_linear;
    vector<double> search_chain, search_linear;
    vector<double> delete_chain, delete_linear;

    for (int n = 1; n <= m; n += 100) { // Iterates in multiples of 100 for speed // 1 by 1 spends at least 7 hours processing :u
        n_values.push_back(n);

        // Create new hash tables
        ChainingTable chainTable(m);
        LinearProbingTable linearTable(m);

        vector<int> keys = generate_keys(n);

        // Measure insert time
        double insert_time_chain = measure_time([&]() {
            for (int key : keys) chainTable.insert(key);
        });
        double insert_time_linear = measure_time([&]() {
            for (int key : keys) linearTable.insert(key);
        });

        // Measure search time
        vector<int> search_keys = generate_keys(n);
        double search_time_chain = measure_time([&]() {
            for (int key : search_keys) chainTable.search(key);
        });
        double search_time_linear = measure_time([&]() {
            for (int key : search_keys) linearTable.search(key);
        });

        // Measure delete time
        vector<int> delete_keys = generate_keys(n);
        double delete_time_chain = measure_time([&]() {
            for (int key : delete_keys) chainTable.remove(key);
        });
        double delete_time_linear = measure_time([&]() {
            for (int key : delete_keys) linearTable.remove(key);
        });

        // Store results
        insert_chain.push_back(insert_time_chain);
        insert_linear.push_back(insert_time_linear);
        search_chain.push_back(search_time_chain);
        search_linear.push_back(search_time_linear);
        delete_chain.push_back(delete_time_chain);
        delete_linear.push_back(delete_time_linear);

        cout << "n=" << n << " | Insert (chaining): " << insert_time_chain << " µs, Insert (linear): " << insert_time_linear << " µs\n";
        cout << "n=" << n << " | Search (chaining): " << search_time_chain << " µs, Search (linear): " << search_time_linear << " µs\n";
        cout << "n=" << n << " | Delete (chaining): " << delete_time_chain << " µs, Delete (linear): " << delete_time_linear << " µs\n";
    }

    // Save data for Python
    freopen("timing_results.csv", "w", stdout);
    cout << "n,insert_chain,insert_linear,search_chain,search_linear,delete_chain,delete_linear\n";
    for (size_t i = 0; i < n_values.size(); i++) {
        cout << n_values[i] << ","
             << insert_chain[i] << "," << insert_linear[i] << ","
             << search_chain[i] << "," << search_linear[i] << ","
             << delete_chain[i] << "," << delete_linear[i] << "\n";
    }
    fclose(stdout);

    return 0;
}
