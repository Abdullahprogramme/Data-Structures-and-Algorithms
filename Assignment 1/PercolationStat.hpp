#ifndef PERCOLATION_STATS_HPP
#define PERCOLATION_STATS_HPP

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Percolation.hpp"
#include "stopwatch.hpp"

using namespace std;

class PercolationStats {
    private:
        int n, T; // grid size and number of trials
        vector<double> thresholds; // percolation thresholds for each trial
        double mean_, stddev_; // mean and standard deviation
        bool statsComputed = false;

        // compute mean and standard deviation
        void computeStats() {
            double sum = 0.0;
            for (double x : thresholds) {
                sum += x;
            }
            mean_ = sum / T;

            double sq = 0.0;
            for (double x : thresholds) {
                sq += (x - mean_) * (x - mean_);
            }
            stddev_ = (T > 1) ? sqrt(sq / (T - 1)) : NAN;
            
            statsComputed = true;
        }

    public:
        // perform independent trials on an n-by-n grid
        PercolationStats(int n_, int trials_) : n(n_), T(trials_) {
            if (n <= 0 || T <= 0) {
                throw invalid_argument("n and trials must be > 0");
            }

            thresholds.resize(T);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, n - 1);

            for (int t = 0; t < T; ++t) {
                Percolation perc(n);
                vector<pair<int, int>> blocked; // (row, col) pairs

                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        blocked.emplace_back(i, j);
                    }
                }

                shuffle(blocked.begin(), blocked.end(), gen); // Shuffle the blocked sites
                
                int opened = 0;
                for (auto& site : blocked) {
                    perc.open(site.first, site.second);
                    opened++;

                    if (perc.percolates()) break;
                }

                thresholds[t] = (double)opened / (n * n);
            }
        }

        // sample mean of percolation threshold
        double mean() {
            if (!statsComputed) computeStats();
            return mean_;
        }

        // sample standard deviation of percolation threshold
        double stddev() {
            if (!statsComputed) computeStats();
            return stddev_;
        }

        // low endpoint of 95% confidence interval
        double confidenceLow() {
            if (!statsComputed) computeStats();
            return mean_ - 1.96 * stddev_ / sqrt(T);
        }

        // high endpoint of 95% confidence interval
        double confidenceHigh() {
            if (!statsComputed) computeStats();
            return mean_ + 1.96 * stddev_ / sqrt(T);
        }

        // test client
        static void test() {
            int n, T;
            cout << "Enter grid size n and number of trials T: ";
            cin >> n >> T;

            Stopwatch sw;
            PercolationStats stats(n, T);
            cout << "mean() = " << stats.mean() << endl;
            cout << "stddev() = " << stats.stddev() << endl;
            cout << "confidenceLow() = " << stats.confidenceLow() << endl;
            cout << "confidenceHigh() = " << stats.confidenceHigh() << endl;
            cout << "elapsed time = " << sw.elapsedTime() << endl;
        }
};

#endif // PERCOLATION_STATS_HPP
