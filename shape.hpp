/**
 * @file shape.hpp
 * @brief Определения геометрических структур
 */

#pragma once
#include <vector>

 /**
  * @struct Point_2
  * @brief 2D точка с координатами x и y
  */
struct Point_2 {
    double x;  ///< Координата X
    double y;  ///< Координата Y
};

/**
 * @struct Line_2
 * @brief 2D линия с начальной и конечной точками
 */
struct Line_2 {
    Point_2 start;  ///< Начальная точка линии
    Point_2 end;    ///< Конечная точка линии
};

/**
 * @struct Shape
 * @brief Геометрическая форма с контуром из точек
 */
struct Shape {
    /**
     * @brief Проверяет, является ли контур прямоугольником
     * @param pts Вектор точек контура
     * @return true если контур является прямоугольником, иначе false
     * @note Проверяет прямые углы и равенство противоположных сторон
     */
    static bool isRectangle(const std::vector<Point_2>& pts);

    std::vector<Point_2> contour;  ///< Вектор точек, описывающих контур формы
};