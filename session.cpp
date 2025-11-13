#include "session.hpp"

#include <string>
#include <simple_svg.hpp>
#include <limits>
#include "shape.hpp"

using namespace session;

bool cmdHandler::isValidArgs(int argc, char* argv[]) const {
    if (argc != 5) return false;
    
    std::string_view arg = argv[ANGLE];
    if (arg != "--angle") {
        return false;
    }
    arg = argv[STEP];
    if (arg != "--step") {
        return false;
    }

    return true;
}

std::vector<Line_2> cmdHandler::inputHatch(const HatchGenerator& hg, Shape& rectangle) const {
    std::vector<Line_2> result;
    rectangle.contour.reserve(4);

    while (true) {
        if (inputRectangle(rectangle)) break;
        std::cerr << "\nThe shape is not a rectangle nor a square";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter angle and step (press Enter Key to skip): ";

    std::string input;
    std::getline(std::cin, input);
    while (!input.empty()) {
        double angle, step;
        std::stringstream ss(input);
        ss >> angle >> step;
        if (ss.fail()) {
            std::cout << "\nError: Invalid values\n";
            std::cout << "Enter angle(degrees) and step (mm): ";
            std::getline(std::cin, input);
        }
        else {
            result = std::move(hg.createRectHatch(rectangle, angle, step));
            return result;
        }
    }

    result = std::move(hg.createRectHatch(rectangle));
    return result;
}

bool cmdHandler::inputRectangle(Shape& rectangle) const {
    rectangle.contour.clear();
    std::cout << "\nInput 4 coordinates\n";
    std::cout << "Order: clockwise or counterclockwise.\n";
    std::cout << "Format: x y (for example: 0 0)\n\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "Enter x y for " << i + 1 << " point: ";
        rectangle.contour.push_back({ 0,0 });
        std::cin >> rectangle.contour[i].x >> rectangle.contour[i].y;
        if (std::cin.fail()) {
            std::cout << "\nError: Invalid value\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            i--;
        }
    }
    return Shape::isRectangle(rectangle.contour);
}


bool session::saveResult(std::vector<Line_2> hatchLines) {
    std::ofstream textFile("output.txt");
    if (textFile.fail()) return false;

    auto saveToStream = [](std::ostream& stream, const auto& line, size_t i) {
        stream << "Line " << i + 1 << ": ("
            << line.start.x << "," << line.start.y << ") -> ("
            << line.end.x << "," << line.end.y << ")\n";
        };

    if (!hatchLines.empty()) std::cout << "\nResult\n";
    for (size_t i = 0; i < hatchLines.size(); ++i) {
        const auto& line = hatchLines[i];
        saveToStream(textFile, line, i);
        saveToStream(std::cout, line, i);
    }
    textFile.close();
    return true;
}

bool session::createSvgFile(const Shape& rectangle, const std::vector<Line_2>& hatch, double scale = 1.) {
    svg::Document svgFile("hatch_rectangle.svg");
    svg::Polygon rectImg(
        svg::Fill(svg::Color::White),
        svg::Stroke(2, svg::Color::Black)
    );
    for (const auto& point : rectangle.contour) {
        rectImg << svg::Point(point.x * scale, point.y * scale);
    }
    svgFile << rectImg;
    for (const auto& line : hatch) {
        svg::Point start_point{
            line.start.x * scale,
            line.start.y * scale
        };
        svg::Point end_point{
            line.end.x * scale,
            line.end.y * scale
        };
        svgFile << svg::Line(start_point, end_point, svg::Stroke(1, svg::Color::Black));
    }
    return svgFile.save();
}
