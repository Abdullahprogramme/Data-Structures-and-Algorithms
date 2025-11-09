#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include "Point2D.hpp"

using namespace std;

class RectHV {
    private:
        double xmin_, ymin_, xmax_, ymax_;

    public:
        RectHV(double xmin, double ymin, double xmax, double ymax) : xmin_(xmin), ymin_(ymin), xmax_(xmax), ymax_(ymax) {
            // Error checking for NaN and invalid coordinates
            if (isnan(xmin_) || isnan(xmax_)) {
                throw invalid_argument("x-coordinate is NaN");
            }
            if (isnan(ymin_) || isnan(ymax_)) {
                throw invalid_argument("y-coordinate is NaN");
            }
            if (xmax_ < xmin_) {
                throw invalid_argument("xmax < xmin");
            }
            if (ymax_ < ymin_) {
                throw invalid_argument("ymax < ymin");
            }
        }

        double xmin() const {
            return xmin_;
        }

        double ymin() const {
            return ymin_;
        }

        double xmax() const { 
            return xmax_;
        }

        double ymax() const {
            return ymax_;
        }

        bool contains(const Point2D& p) const {
            return p.x() >= xmin_ && p.x() <= xmax_ && p.y() >= ymin_ && p.y() <= ymax_;
        }

        bool intersects(const RectHV& that) const {
            return xmax_ >= that.xmin_ && ymax_ >= that.ymin_ && that.xmax_ >= xmin_ && that.ymax_ >= ymin_;
        }

        double distanceSquaredTo(const Point2D& p) const {
            double dx = 0.0, dy = 0.0;

            if (p.x() < xmin_) {
                dx = p.x() - xmin_;
            } else if (p.x() > xmax_) {
                dx = p.x() - xmax_;
            }

            if (p.y() < ymin_) {
                dy = p.y() - ymin_;
            } else if (p.y() > ymax_) {
                dy = p.y() - ymax_;
            }

            return pow(dx, 2) + pow(dy, 2);
        }

        bool operator==(const RectHV& other) const {
            return xmin_ == other.xmin_ && ymin_ == other.ymin_ && xmax_ == other.xmax_ && ymax_ == other.ymax_;
        }

        friend ostream& operator<<(ostream& os, const RectHV& point);
};

inline ostream& operator<<(ostream& os, const RectHV& rect) {
    return os << "[" << rect.xmin() << ", " << rect.xmax() << "] x [" << rect.ymin() << ", " << rect.ymax() << "]";
}

