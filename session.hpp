/**
 * @file session.hpp
 * @brief Управление сессией и обработка ввода/вывода
 */

#pragma once

#include "hatch_generator.hpp"

 /**
  * @namespace session
  * @brief Пространство имен для управления пользовательской сессией
  */
namespace session {

    /**
     * @enum ArgIndex
     * @brief Индексы аргументов командной строки
     */
    enum ArgIndex {
        ANGLE = 1,        ///< Индекс аргумента --angle
        ANGLE_VALUE = 2,  ///< Индекс значения угла
        STEP = 3,         ///< Индекс аргумента --step  
        STEP_VALUE = 4    ///< Индекс значения шага
    };

    /**
     * @class cmdHandler
     * @brief Обработчик командной строки и пользовательского ввода
     */
    class cmdHandler {
    public:
        /**
         * @brief Проверяет корректность аргументов командной строки
         * @param argc Количество аргументов
         * @param argv Массив аргументов
         * @return true если аргументы корректны, иначе false
         */
        bool isValidArgs(int argc, char* argv[]) const;

        /**
         * @brief Обрабатывает ввод пользователя и генерирует штриховку
         * @param hatch Генератор штриховки
         * @param contours Контур для штриховки
         * @return Вектор линий штриховки
         */
        std::vector<Line_2> inputHatch(const HatchGenerator& hatch, Shape& contours) const;

    private:
        /**
         * @brief Запрашивает у пользователя ввод прямоугольного контура
         * @param rectangle Форма для заполнения точками контура
         * @return true если введенный контур является прямоугольником
         */
        bool inputRectangle(Shape& rectangle) const;
    };

    /**
     * @brief Сохраняет результат в текстовый файл
     * @param hatchLines Вектор линий штриховки для сохранения
     * @return true если сохранение успешно, иначе false
     */
    bool saveResult(std::vector<Line_2> hatchLines);

    /**
     * @brief Создает SVG файл с визуализацией
     * @param rectangle Прямоугольный контур
     * @param hatch Линии штриховки
     * @param scale Масштаб для визуализации
     * @return true если создание успешно, иначе false
     */
    bool createSvgFile(const Shape& rectangle, const std::vector<Line_2>& hatch, double scale);

} // namespace session