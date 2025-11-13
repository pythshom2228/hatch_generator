#pragma once
#include <vector>

struct Point_2 {
    double x;
    double y;
};


struct Line_2 {
    Point_2 start;
    Point_2 end;
};

struct Shape {

    static bool isRectangle(const std::vector<Point_2>& pts);

    std::vector<Point_2> contour;
};