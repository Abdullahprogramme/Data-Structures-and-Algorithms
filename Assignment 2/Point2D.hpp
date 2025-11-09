#pragma once

#include <iostream>
using namespace std;

class Point2D {
    private:
        double x_, y_;

    public:
        Point2D(double x, double y) : x_(x), y_(y) {}

        double x() const {
            return x_;
        }

        double y() const {
            return y_;
        }

        double distanceSquaredTo(const Point2D& that) const {
            double dx = x_ - that.x_;
            double dy = y_ - that.y_;
            return dx * dx + dy * dy;
        }

        bool operator==(const Point2D& other) const {
            return x_ == other.x_ && y_ == other.y_;
        }

        bool operator<(const Point2D& other) const {
            if (y_ < other.y_) return 1;
            if (y_ > other.y_) return 0;
            if (x_ < other.x_) return 1;
            if (x_ > other.x_) return 0;
            return 0;
        }

        bool operator!=(const Point2D& other) const {
            return !(*this == other);
        }

        friend ostream& operator<<(ostream& os, const Point2D& point);
};

inline ostream& operator<<(ostream& os, const Point2D& point) {
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
}
