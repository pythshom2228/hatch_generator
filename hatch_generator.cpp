#include "hatch_generator.hpp"

#include <vector>
#include <cmath>
#include <stdexcept>
#include "math_linear.hpp"

HatchGenerator::HatchGenerator(const std::string& defaultAngle, const std::string& defaultStep)
  : _defaultAngle(std::stod(defaultAngle)),
    _defaultStep(std::stod(defaultStep)) {
    if (_defaultStep <= 0) {
        throw std::invalid_argument("Step must be greater than zero");
    }
}

HatchGenerator::HatchGenerator(double defaultAngle, double defaultStep)
  : _defaultAngle(defaultAngle),
    _defaultStep(defaultStep) {}

std::vector<Line_2> HatchGenerator::createRectHatch(
    const Shape& rectangle, double angleDegrees, double step) const {
    std::vector<Line_2> lines;
    if (!Shape::isRectangle(rectangle.contour)) return lines;

    // Вычислить границы и углы прямоугольника
    double minX = rectangle.contour[0].x, maxX = minX;
    double minY = rectangle.contour[0].y, maxY = minY;
    for (const auto& p : rectangle.contour) {
        minX = std::min(minX, p.x);
        maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y);
        maxY = std::max(maxY, p.y);
    }

    double angleRad = angleDegrees * PI / 180.0;
    double cosA = std::cos(angleRad);
    double sinA = std::sin(angleRad);

    // Вектор нормали
    double nx = -sinA;
    double ny = cosA;

    // Спроецируйте все углы на нормаль
    double d_min = 1e9, d_max = -1e9;
    for (const auto& p : rectangle.contour) {
        double d = p.x * nx + p.y * ny;
        d_min = std::min(d_min, d);
        d_max = std::max(d_max, d);
    }

    // Сгенерировать линии штриховки с шагом
    for (double d = d_min - step; d <= d_max + step; d += step) {
        // Вектор направления штриховки
        double dx = cosA;
        double dy = sinA;

        // Выберем точку на линии
        double x0 = nx * d;
        double y0 = ny * d;

        Line_2 line;
        line.start.x = x0 - 10000 * dx;
        line.start.y = y0 - 10000 * dy;
        line.end.x   = x0 + 10000 * dx;
        line.end.y   = y0 + 10000 * dy;

        // Обрезать до прямоугольника
        std::vector<Point_2> intersections;
        for (size_t i = 0; i < 4; ++i) {
            Point_2 p1 = rectangle.contour[i];
            Point_2 p2 = rectangle.contour[(i + 1) % 4];
            double x1 = line.start.x, y1 = line.start.y;
            double x2 = line.end.x,   y2 = line.end.y;
            double x3 = p1.x, y3 = p1.y;
            double x4 = p2.x, y4 = p2.y;

            double denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
            if (std::abs(denom) < 1e-9) continue;

            double t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) / denom;
            double u = -((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3)) / denom;

            if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
                Point_2 inter;
                inter.x = x1 + t * (x2 - x1);
                inter.y = y1 + t * (y2 - y1);
                intersections.push_back(inter);
            }
        }

        if (intersections.size() == 2) {
            lines.push_back({ intersections[0], intersections[1] });
        }
    }

    return lines;
}

std::vector<Line_2> HatchGenerator::createRectHatch(const Shape& rectangle) const {
    return createRectHatch(rectangle, _defaultAngle, _defaultStep);
}