#include "shape.hpp"
#include "math_linear.hpp"

bool Shape::isRectangle(const std::vector<Point_2>& pts) {
    if (pts.size() != 4) return false;

    // Проверяем углы (AB ⟂ BC, BC ⟂ CD, CD ⟂ DA, DA ⟂ AB)
    double eps = 1e-6;
    bool rightAngles =
        std::abs(dot(pts[3], pts[0], pts[1])) < eps &&
        std::abs(dot(pts[0], pts[1], pts[2])) < eps &&
        std::abs(dot(pts[1], pts[2], pts[3])) < eps &&
        std::abs(dot(pts[2], pts[3], pts[0])) < eps;

    if (!rightAngles) return false;

    // Проверяем равенство противоположных сторон
    double d01 = distance(pts[0], pts[1]);
    double d12 = distance(pts[1], pts[2]);
    double d23 = distance(pts[2], pts[3]);
    double d30 = distance(pts[3], pts[0]);

    bool equalOpposite = std::abs(d01 - d23) < eps && std::abs(d12 - d30) < eps;
    return equalOpposite;
}