#pragma once

#include <chrono>
#include <ratio>

using namespace std;

// number of seconds per tick of the high-resolution clock
const double PERIOD = (double) chrono::high_resolution_clock::period::num / chrono::high_resolution_clock::period::den;

class Stopwatch {
    private:
        chrono::time_point<chrono::high_resolution_clock> start; 
        
    public:
        Stopwatch() : start {chrono::high_resolution_clock::now()} {
        }

        void reset() {
            start = chrono::high_resolution_clock::now();
        }

        double elapsedTime() const {
            const auto now = chrono::high_resolution_clock::now();
            return ((now - start).count()) * PERIOD; // convert to seconds and return
        }
};