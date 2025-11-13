#include <iostream>

#include "session.hpp"
#include "hatch_generator.hpp"

int main(int argc, char* argv[]) {
    using namespace session;

    cmdHandler handler;
    if (!handler.isValidArgs(argc, argv)) {
        std::cerr << "Usage: ./hatch_generator --angle <degrees> --step <mm>\n";
        return EXIT_FAILURE;
    }

    try {
        HatchGenerator hg(argv[ANGLE_VALUE], argv[STEP_VALUE]);
        std::vector<Shape> contours = { Shape{} };

        std::cout << "Make rectangle\n";
        std::vector<Line_2> hatchLines = std::move(handler.inputHatch(hg, contours[0]));

        if (!saveResult(hatchLines)) {
            std::cerr << "Failed to create a text file\n";
            return EXIT_FAILURE;
        }
        if (!createSvgFile(contours[0], hatchLines, 10)) {
            std::cerr << "Failed to create an svg file\n";
            return EXIT_FAILURE;
        }
    }
    catch (const std::invalid_argument& ex) {
        std::cerr << "Error: Invalid input\n" << ex.what();
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Error: Something went wrong\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
