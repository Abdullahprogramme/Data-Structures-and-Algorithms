#pragma once

#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

class Svector {
    private:
        map<int, double> data;

    public:
        Svector() = default;

        void set(int i, double x) {
            if (x != 0.0) {
                data[i] = x;
            } else {
                data.erase(i);
            }
        }

        double get(int i) const {
            auto it = data.find(i);
            if (it != data.end()) {
                return it->second;
            }

            return 0.0;
        }

        double dot(const Svector& that) const {
            double result = 0.0;

            for (const auto& [key, value] : data) {
                auto it = that.data.find(key);
                if (it != that.data.end()) {
                    result += value * it->second;
                }
            }

            return result;
        }

        double norm() const {
            double sum = 0.0;

            for (const auto& [key, value] : data) {
                sum += pow(value, 2);
            }

            return sqrt(sum);
        }

        Svector add(const Svector& that) const {
            Svector result = *this;

            for (const auto& [key, value] : that.data) {
                result.set(key, result.get(key) + value);
            }

            return result;
        }

        void scale(double alpha) {
            for_each(data.begin(), data.end(), [alpha](auto& pair) {
                pair.second *= alpha;
            });
        }

        void  print() const {
            for (const auto& [key, value] : data) {
                cout << "(" << key << ", " << fixed << setprecision(1) << value << ") ";
            }
            cout << endl;
        }
};
