#pragma once
#include <vector>
#include <string>
#include "shape.hpp"

class HatchGenerator {
public:

    HatchGenerator(const std::string& defaultAngle, const std::string& defaultStep);
    
    HatchGenerator(double defaultAngle, double defaultStep);

    std::vector<Line_2> createRectHatch(const Shape& rectangle, double angleDegrees, double step) const;
    
    std::vector<Line_2> createRectHatch(const Shape& rectangle) const;
    
private:
    const double _defaultAngle;
    const double _defaultStep;
};