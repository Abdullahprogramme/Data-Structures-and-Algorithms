#pragma once

#include <chrono>
using namespace std;

class StopWatch {
    private:
        chrono::high_resolution_clock::time_point start_time_;
        bool running_ = false;

    public:
        StopWatch() = default;

        void start() {
            start_time_ = chrono::high_resolution_clock::now();
            running_ = true;
        }

        // returns elapsed seconds since start() was called
        double elapsedSeconds() const {
            if (!running_) return 0.0;

            auto now = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = now - start_time_;
            
            return diff.count();
        }
};
