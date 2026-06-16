#include "inertia.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

float readFloat(const std::string &prompt) {
  while (true) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);

    if (std::cin.eof()) {
      throw std::runtime_error{"Обнаружен конец ввода"};
    }

    try {
      size_t pos{};
      float value = std::stof(input, &pos);
      if (pos != input.length()) {
        throw std::invalid_argument{"Ошибка! Введите число"};
      }
      return value;
    } catch (const std::invalid_argument &) {
      std::cout << "Ошибка! Введите число: ";
    } catch (const std::out_of_range &) {
      std::cout << "Число слишком большое. Попробуйте ещё раз: ";
    }
  }
}

Eigen::Vector3f normalizeVector(float x, float y, float z) {
  Eigen::Vector3f v{x, y, z};
  float len{v.norm()};
  if (len == 0) {
    throw std::invalid_argument{"Ошибка: нулевой вектор!"};
  }
  return v / len;
}

Eigen::Matrix3f inertiaCube(float mass, float side) {
  Eigen::Matrix3f I{};
  I.setZero();
  float val{mass * side * side / 6.0f};
  I(0, 0) = val;
  I(1, 1) = val;
  I(2, 2) = val;
  return I;
}

Eigen::Matrix3f inertiaSphere(float mass, float radius) {
  Eigen::Matrix3f I{};
  I.setZero();
  float val{0.4f * mass * radius * radius};
  I(0, 0) = val;
  I(1, 1) = val;
  I(2, 2) = val;
  return I;
}

Eigen::Matrix3f inertiaBox(float mass, float a, float b, float c) {
  Eigen::Matrix3f I{};
  I.setZero();
  I(0, 0) = mass * (b * b + c * c) / 12.0f;
  I(1, 1) = mass * (a * a + c * c) / 12.0f;
  I(2, 2) = mass * (a * a + b * b) / 12.0f;
  return I;
}

Eigen::Matrix3f inertiaCylinder(float mass, float radius, float length) {
  Eigen::Matrix3f I{};
  I.setZero();
  I(0, 0) = mass * radius * radius / 2.0f;
  I(1, 1) = mass * (3 * radius * radius + length * length) / 12.0f;
  I(2, 2) = I(1, 1);
  return I;
}

Eigen::Matrix3f inertiaCone(float mass, float radius, float height) {
  Eigen::Matrix3f I{};
  I.setZero();
  float Ixx{(3.0f / 20.0f) * mass * (radius * radius + height * height / 4.0f)};
  float Izz{(3.0f / 10.0f) * mass * radius * radius};
  I(0, 0) = Ixx;
  I(1, 1) = Ixx;
  I(2, 2) = Izz;
  return I;
}
