/**
 * @file math_linear.hpp
 * @brief Математические функции для линейной алгебры
 */

#pragma once

struct Point_2;

constexpr double PI = 3.14159265358979323846;  ///< Число Pi для математических вычислений

/**
 * @brief Вычисляет скалярное произведение векторов
 * @param a Первая точка
 * @param b Вторая точка (вершина угла)
 * @param c Третья точка
 * @return Скалярное произведение векторов AB и BC
 */
double dot(const Point_2& a, const Point_2& b, const Point_2& c);

/**
 * @brief Вычисляет расстояние между двумя точками
 * @param a Первая точка
 * @param b Вторая точка
 * @return Евклидово расстояние между точками
 */
double distance(const Point_2& a, const Point_2& b);