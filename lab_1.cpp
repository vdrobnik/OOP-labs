#include <iostream>
#include <functional>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

// Базовый абстрактный класс для численного расчета интегралов
class NumericalIntegration {
protected:
    int numPoints;      // Число точек
    double stepSize;    // Шаг
    double precision;   // Точность

public:
    NumericalIntegration(int numPoints_, double stepSize_, double precision_)
        : numPoints(numPoints_), stepSize(stepSize_), precision(precision_) {}

    // Метод для расчета интеграла
    virtual double Calc(std::function<double(double)> f, double lowerBound, double upperBound) = 0;
};

// Производный класс для расчета интегралов методом трапеций
class TrapezoidalIntegration : public NumericalIntegration {
public:
    TrapezoidalIntegration(int numPoints_, double stepSize_, double precision_)
        : NumericalIntegration(numPoints_, stepSize_, precision_) {}

    // Переопределение метода Calc для метода трапеций
    double Calc(std::function<double(double)> f, double lowerBound, double upperBound) override {
        double integral = 0.0;
        double x = lowerBound;

        for (int i = 0; i <= numPoints; ++i) {
            if (i == 0 || i == numPoints) {
                integral += f(x) / 2.0;
            }
            else {
                integral += f(x);
            }

            x += stepSize;
        }

        integral *= stepSize;
        return integral;
    }
};

// Производный класс для расчета интегралов методом Симпсона
class SimpsonIntegration : public NumericalIntegration {
public:
    SimpsonIntegration(int numPoints_, double stepSize_, double precision_)
        : NumericalIntegration(numPoints_, stepSize_, precision_) {}

    // Переопределение метода Calc для метода Симпсона
    double Calc(std::function<double(double)> f, double lowerBound, double upperBound) override {
        double integral = 0.0;
        double x = lowerBound;

        for (int i = 0; i <= numPoints; ++i) {
            if (i == 0 || i == numPoints) {
                integral += f(x);
            }
            else if (i % 2 == 0) {
                integral += 2.0 * f(x);
            }
            else {
                integral += 4.0 * f(x);
            }

            x += stepSize;
        }

        integral *= stepSize / 3.0;
        return integral;
    }
};

int main() {
    // Создаем объекты классов для расчета интегралов
    TrapezoidalIntegration trapezoidal(100, 0.01, 1e-6);
    SimpsonIntegration simpson(100, 0.01, 1e-6);

    // Задаем подынтегральное выражение в виде функции
    auto function = [](double x) { return std::sin(x); };

    // Задаем границы интегрирования
    const double M_PI = 3.14159;
    double lowerBound = 0.0;
    double upperBound = M_PI;

    // Вычисляем интеграл методом трапеций
    double resultTrapezoidal = trapezoidal.Calc(function, lowerBound, upperBound);

    // Вычисляем интеграл методом Симпсона
    double resultSimpson = simpson.Calc(function, lowerBound, upperBound);

    // Выводим результаты
    std::cout << "Интеграл методом трапеций: " << resultTrapezoidal << std::endl;
    std::cout << "Интеграл методом Симпсона: " << resultSimpson << std::endl;

    _getch();
}