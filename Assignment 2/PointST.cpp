#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#include "Point2D.hpp"
#include "RectHV.hpp"
#include "StopWatch.hpp"

using namespace std;

template <typename Value>
class PointST {
    private:
        map<Point2D, Value> point_map_;

    public:
        using iterator = typename map<Point2D, Value>::const_iterator;

        PointST() {}

        // is the symbol table empty?
        bool empty() const {
            return point_map_.empty();
        }   

        // number of points
        int size() const {
            return point_map_.size();
        }

        // associate the value val with point p
        void put(const Point2D& p, const Value& val) {
            point_map_[p] = val;
        }

        // value associated with point p
        Value& get(const Point2D& p) {
            return point_map_.at(p);
        }

        // value associated with point p
        Value& operator[](const Point2D& p) {
            return point_map_[p];
        }

        // does the symbol table contain point p?
        bool contains(const Point2D& p) const {
            return point_map_.find(p) != point_map_.end();
        }

        // all points that are inside the rectangle (or on the boundary)
        vector<Point2D> range(const RectHV& rect) const {
            vector<Point2D> points_in_range;

            // iterating through all points in the map to see which are in the rectangle
            for_each(point_map_.begin(), point_map_.end(), [&](const pair<Point2D, Value>& entry) {
                if (rect.contains(entry.first)) {
                    points_in_range.push_back(entry.first);
                }
            });

            return points_in_range;
        }

        // nearest neighbor of point p
        Point2D nearest(const Point2D& p) const {
            if (empty()) { // Check if the symbol table is empty
                throw runtime_error("Symbol table is empty");
            }

            Point2D nearest_point = point_map_.begin()->first; // Initialize with the first point in the map
            double nearest_distance = p.distanceSquaredTo(nearest_point); // Initialize with the distance to the first point

            for_each(point_map_.begin(), point_map_.end(), [&](const pair<Point2D, Value>& entry) {
                double current_distance = p.distanceSquaredTo(entry.first);
                if (current_distance < nearest_distance) {
                    nearest_distance = current_distance;
                    nearest_point = entry.first;
                }
            });

            return nearest_point;
        }

        // iterator to first [point, value] pair in the symbol table
        iterator begin() const {
            return point_map_.cbegin();
        }

        // iterator to one past the last [point, value] pair in the symbol table
        iterator end() const {
            return point_map_.cend();
        }
};

// --- main with tests for PointST ---
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filename = (argc > 1) ? argv[1] : "inputs/input5.txt";
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: cannot open input file '" << filename << "'\n";
        return 1;
    }

    vector<Point2D> points;
    double x, y;
    while (infile >> x >> y) {
        points.emplace_back(x, y);
    }

    PointST<int> st;
    int idx = 0;
    for (const auto& p : points) {
        st.put(p, idx++);
    }

    cout << "Inserted " << st.size() << " points\n";
    if (!points.empty()) {
        cout << "Contains first point " << points[0] << ": " << (st.contains(points[0]) ? "yes" : "no") << "\n";
        cout << "Value at first point: " << st.get(points[0]) << "\n";
    }

    // Iterate through all points
    cout << "All points in the symbol table:\n";
    for (auto it = st.begin(); it != st.end(); ++it) {
        cout << "  " << it->first << " -> " << it->second << '\n';
    }

    // Test range
    RectHV r(0.0, 0.0, 0.5, 0.5);
    auto inside = st.range(r);
    cout << "Points inside rectangle " << r << ":\n";
    for (const auto& p : inside) cout << "  " << p << '\n';

    // Test nearest
    Point2D q(0.65, 0.5);
    if (!st.empty()) {
        cout << "Nearest to " << q << " is " << st.nearest(q) << "\n";
    }

    // Performance test: m calls to nearest() with random points in unit square
    const int m = 40000;
    StopWatch sw;
    srand((unsigned)time(nullptr));
    volatile double sink = 0.0; // prevent optimizer from removing calls
    sw.start();

    for (int i = 0; i < m; ++i) {
        double rx = (double)rand() / RAND_MAX;
        double ry = (double)rand() / RAND_MAX;
        Point2D rq(rx, ry);
        // compute a small value
        sink += st.nearest(rq).distanceSquaredTo(rq);
    }

    double secs = sw.elapsedSeconds();
    cout << m << " calls to nearest() took " << secs << " s (" << (m / secs) << " calls/s)\n";

    
    if (sink < 0) cout << sink << '\n';

    return 0;
}