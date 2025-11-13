#include "math_linear.hpp"

#include <cmath>
#include "hatch_generator.hpp"

double dot(const Point_2& a, const Point_2& b, const Point_2& c) {
    // ¬озвращает скал€рное произведение векторов AB и BC
    double abx = b.x - a.x;
    double aby = b.y - a.y;
    double bcx = c.x - b.x;
    double bcy = c.y - b.y;
    return abx * bcx + aby * bcy;
}

double distance(const Point_2& a, const Point_2& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}