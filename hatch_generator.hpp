/**
 * @file hatch_generator.hpp
 * @brief Основной класс для генерации штриховки
 * @version 1.0
 * @date 2025
 */

#pragma once
#include <vector>
#include <string>
#include "shape.hpp"

 /**
  * @class HatchGenerator
  * @brief Генератор штриховки для прямоугольных контуров
  *
  * Класс отвечает за создание линий штриховки внутри прямоугольных контуров
  * с заданным углом наклона и шагом между линиями.
  */
class HatchGenerator {
public:
    /**
     * @brief Конструктор с строковыми параметрами
     * @param defaultAngle Угол наклона штриховки в градусах (строковый формат)
     * @param defaultStep Шаг между линиями штриховки (строковый формат)
     * @throws std::invalid_argument Если шаг меньше или равен нулю
     */
    HatchGenerator(const std::string& defaultAngle, const std::string& defaultStep);

    /**
     * @brief Конструктор с числовыми параметрами
     * @param defaultAngle Угол наклона штриховки в градусах
     * @param defaultStep Шаг между линиями штриховки
     */
    HatchGenerator(double defaultAngle, double defaultStep);

    /**
     * @brief Генерирует штриховку для прямоугольника с указанными параметрами
     * @param rectangle Прямоугольный контур для штриховки
     * @param angleDegrees Угол наклона линий в градусах (0-180)
     * @param step Шаг между линиями штриховки
     * @return Вектор линий штриховки внутри контура
     * @note Возвращает пустой вектор если контур не является прямоугольником
     */
    std::vector<Line_2> createRectHatch(const Shape& rectangle, double angleDegrees, double step) const;

    /**
     * @brief Генерирует штриховку с параметрами по умолчанию
     * @param rectangle Прямоугольный контур для штриховки
     * @return Вектор линий штриховки
     */
    std::vector<Line_2> createRectHatch(const Shape& rectangle) const;

private:
    const double _defaultAngle;  ///< Угол наклона по умолчанию
    const double _defaultStep;   ///< Шаг по умолчанию
};