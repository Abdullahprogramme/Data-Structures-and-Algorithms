
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <fstream>

#include "Point2D.hpp"
#include "RectHV.hpp"
#include "StopWatch.hpp"

using namespace std;

#define negInf -numeric_limits<double>::infinity()
#define posInf numeric_limits<double>::infinity()

template <typename Value>
class KdTreeST {
    private:
        struct Node {
            Point2D p;
            Value val;
            RectHV rect;
            unique_ptr<Node> left;
            unique_ptr<Node> right;

            Node(const Point2D& point, const Value& value, const RectHV& r)
                : p(point), val(value), rect(r), left(nullptr), right(nullptr) {}
        };

        unique_ptr<Node> root_;
        int n_ = 0;
        
        // cache of points in level order
        mutable vector<Point2D> level_cache_;
        mutable bool cache_valid_ = false;

        // helper to find node with point p
        Node* find_node(Node* x, const Point2D& p, bool vertical) const {
            if (!x) return nullptr;
            if (x->p == p) return x;

            // if vertical split, compare x-coordinates, if fails then y-coordinates
            if (vertical) {
                if (p.x() < x->p.x() || (p.x() == x->p.x() && p.y() < x->p.y())) return find_node(x->left.get(), p, !vertical);
                else return find_node(x->right.get(), p, !vertical);
            // if horizontal split, compare y-coordinates, if fails then x-coordinates
            } else {
                if (p.y() < x->p.y() || (p.y() == x->p.y() && p.x() < x->p.x())) return find_node(x->left.get(), p, !vertical);
                else return find_node(x->right.get(), p, !vertical);
            }
        }

        void putRec(unique_ptr<Node>& x, const Point2D& p, const Value& val, bool vertical, const RectHV& rect) {
            if (!x) {
                x = make_unique<Node>(p, val, rect);
                ++n_;
                cache_valid_ = false;
                return;
            }

            if (x->p == p) {
                x->val = val; // update
                return;
            }

            // if vertical split, compare x-coordinates, if fails then y-coordinates
            if (vertical) {
                if (p.x() < x->p.x() || (p.x() == x->p.x() && p.y() < x->p.y())) {
                    // left: x-range [rect.xmin(), x->p.x()]
                    RectHV leftRect(rect.xmin(), rect.ymin(), x->p.x(), rect.ymax());
                    putRec(x->left, p, val, !vertical, leftRect);
                } else {
                    RectHV rightRect(x->p.x(), rect.ymin(), rect.xmax(), rect.ymax());
                    putRec(x->right, p, val, !vertical, rightRect);
                }

            // if horizontal split, compare y-coordinates, if fails then x-coordinates
            } else {
                if (p.y() < x->p.y() || (p.y() == x->p.y() && p.x() < x->p.x())) {
                    RectHV bottomRect(rect.xmin(), rect.ymin(), rect.xmax(), x->p.y());
                    putRec(x->left, p, val, !vertical, bottomRect);
                } else {
                    RectHV topRect(rect.xmin(), x->p.y(), rect.xmax(), rect.ymax());
                    putRec(x->right, p, val, !vertical, topRect);
                }
            }
        }

        void rangeRec(const Node* x, const RectHV& query, vector<Point2D>& result) const {
            if (!x) return;
            if (!x->rect.intersects(query)) return; // prune

            if (query.contains(x->p)) result.push_back(x->p);

            rangeRec(x->left.get(), query, result);
            rangeRec(x->right.get(), query, result);
        }

        void nearestRec(const Node* x, const Point2D& query, Point2D& bestP, double& bestDist, bool vertical) const {
            if (!x) return;

            double d = query.distanceSquaredTo(x->p);
            if (d < bestDist) {
                bestDist = d;
                bestP = x->p;
            }

            // choose subtree that is on same side as query first
            const Node* first = nullptr;
            const Node* second = nullptr;

            // if vertical split, compare x-coordinates, if fails then y-coordinates
            if (vertical) {
                if (query.x() < x->p.x() || (query.x() == x->p.x() && query.y() < x->p.y())) {
                    first = x->left.get();
                    second = x->right.get();
                } else {
                    first = x->right.get();
                    second = x->left.get();
                }
            
            // if horizontal split, compare y-coordinates, if fails then x-coordinates
            } else {
                if (query.y() < x->p.y() || (query.y() == x->p.y() && query.x() < x->p.x())) {
                    first = x->left.get();
                    second = x->right.get();
                } else {
                    first = x->right.get();
                    second = x->left.get();
                }
            }

            if (first) nearestRec(first, query, bestP, bestDist, !vertical);

            if (second) {
                double rectDist = second->rect.distanceSquaredTo(query);
                if (rectDist < bestDist) {
                    nearestRec(second, query, bestP, bestDist, !vertical);
                }
            }
        }

        void build_level_cache() const {
            level_cache_.clear();
            if (!root_) return;

            queue<const Node*> q;
            q.push(root_.get());

            while (!q.empty()) {
                const Node* cur = q.front(); q.pop();
                level_cache_.push_back(cur->p);

                if (cur->left) q.push(cur->left.get());
                if (cur->right) q.push(cur->right.get());
            }

            cache_valid_ = true;
        }

    public:
        using iterator = typename vector<Point2D>::const_iterator;

        KdTreeST() : root_(nullptr), n_(0), level_cache_(), cache_valid_(false) {}

        bool empty() const { 
            return n_ == 0; 
        }

        int size() const { 
            return n_; 
        }

        void put(const Point2D& p, const Value& val) {
            RectHV rootRect(negInf, negInf, posInf, posInf);
            putRec(root_, p, val, true, rootRect);
        }

        bool contains(const Point2D& p) const {
            return find_node(root_.get(), p, true) != nullptr;
        }

        Value& get(const Point2D& p) {
            Node* x = find_node(root_.get(), p, true);
            if (!x) throw runtime_error("Point not found");

            return x->val;
        }

        Value& operator[](const Point2D& p) {
            Node* x = find_node(root_.get(), p, true);
            if (x) return x->val;

            // insert default value
            Value defaultVal{};
            put(p, defaultVal);
            x = find_node(root_.get(), p, true);

            return x->val;
        }

        vector<Point2D> range(const RectHV& query) const {
            vector<Point2D> result;
            rangeRec(root_.get(), query, result);

            return result;
        }

        Point2D nearest(const Point2D& query) const {
            if (empty()) throw runtime_error("Symbol table is empty");
            
            Point2D bestP = root_->p;
            double bestDist = query.distanceSquaredTo(bestP);
            nearestRec(root_.get(), query, bestP, bestDist, true);

            return bestP;
        }

        // level-order iterators over points
        iterator begin() const {
            if (!cache_valid_) build_level_cache();
            return level_cache_.cbegin();
        }

        iterator end() const {
            if (!cache_valid_) build_level_cache();
            return level_cache_.cend();
        }
};

// --- main with tests for KdTreeST ---
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

    KdTreeST<int> st;
    int idx = 0;
    for (const auto& p : points) st.put(p, idx++);

    cout << "Inserted " << st.size() << " points\n";

    // level-order traversal using begin/end
    cout << "Level-order traversal:\n";
    for (auto it = st.begin(); it != st.end(); ++it) {
        cout << "  " << *it << '\n';
    }

    // range query
    RectHV query(0.0, 0.0, 0.5, 0.5);
    auto inrange = st.range(query);
    cout << "Points inside rectangle " << query << ":\n";
    for (const auto& p : inrange) cout << "  " << p << '\n';

    // nearest
    Point2D q(0.65, 0.5);
    cout << "Nearest to " << q << " is " << st.nearest(q) << "\n";

    // Performance test: m calls to nearest() with random points in unit square
    const long long m = 4000000;
    StopWatch sw;
    srand((unsigned)time(nullptr));
    volatile double sink = 0.0;
    sw.start();

    for (long long i = 0; i < m; ++i) {
        double rx = (double)rand() / RAND_MAX;
        double ry = (double)rand() / RAND_MAX;
        Point2D rq(rx, ry);
        
        sink += st.nearest(rq).distanceSquaredTo(rq);
    }
    
    double secs = sw.elapsedSeconds();
    cout << m << " calls to nearest() took " << secs << " s (" << (m / secs) << " calls/s)\n";

    
    if (sink < 0) cout << sink << '\n';

    return 0;
}