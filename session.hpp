#pragma once

#include "hatch_generator.hpp"

namespace session {

    enum ArgIndex {
        ANGLE = 1,
        ANGLE_VALUE = 2,
        STEP = 3,
        STEP_VALUE = 4
    };

    class cmdHandler {
    public:

        bool isValidArgs(int argc, char* argv[]) const;
        std::vector<Line_2> inputHatch(const HatchGenerator& hatch, Shape& contours) const;    

    private:
        bool inputRectangle(Shape& rectangle) const;
    };

    bool saveResult(std::vector<Line_2> hatchLines);
    bool createSvgFile(const Shape& rectangle, const std::vector<Line_2>& hatch, double scale);

} // namespace session