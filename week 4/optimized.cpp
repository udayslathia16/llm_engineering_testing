
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <limits> // Required for numeric_limits

// Use a faster PRNG
uint32_t lcg(uint32_t& seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u * 2u) { // m = 2**32
    seed = (a * seed + c) % m;
    return seed;
}

int64_t max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    uint32_t value = seed;
    int64_t max_sum = std::numeric_limits<int64_t>::min(); // Initialize with lowest possible value
    int64_t current_sum = 0;
    int32_t num; // to store generated number

    for (int i = 0; i < n; ++i) {
        value = lcg(value);
        num = value % (max_val - min_val + 1) + min_val;
        current_sum = 0; // Reset current sum for each starting position
        for (int j = i; j < n; ++j) {

            current_sum += num;
            max_sum = std::max(max_sum, current_sum);
             value = lcg(value);
             num = value % (max_val - min_val + 1) + min_val;
        }
    }
    return max_sum;
}

int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    uint32_t seed = initial_seed;

    for (int _ = 0; _ < 20; ++_) {
        seed = lcg(seed); // Modifying to advance the seed
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    // Parameters
    int n = 10000;         // Number of random numbers
    uint32_t initial_seed = 42; // Initial seed for the LCG
    int min_val = -10;     // Minimum value of random numbers
    int max_val = 10;      // Maximum value of random numbers

    // Timing the function
    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << static_cast<double>(duration.count()) / 1000000.0 << " seconds" << std::endl;

    return 0;
}

