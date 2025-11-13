/**
 * @file main.cpp
 * @brief Главная функция программы
 * @mainpage Генератор штриховки для SLM-слайсера
 *
 * Программа для генерации штриховки внутри прямоугольных контуров
 * с возможностью настройки угла наклона и шага между линиями.
 *
 * Использование:
 * @code
 * ./hatch_generator --angle <degrees> --step <mm>
 * @endcode
 *
 * @version 1.0
 */

#include <iostream>
#include "session.hpp"
#include "hatch_generator.hpp"

 /**
  * @brief Точка входа в программу
  * @param argc Количество аргументов командной строки
  * @param argv Массив аргументов командной строки
  * @return EXIT_SUCCESS при успешном выполнении, EXIT_FAILURE при ошибке
  *
  * @par Пример использования:
  * @code{.sh}
  * ./hatch_generator --angle 45 --step 1
  * @endcode
  */
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