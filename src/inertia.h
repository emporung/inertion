#ifndef INERTIA_H
#define INERTIA_H

#include <Eigen/Dense>
#include <string>

// Вспомогательные функции
float readFloat(const std::string& prompt);
Eigen::Vector3f normalizeVector(float x, float y, float z);

// Тензоры инерции
Eigen::Matrix3f inertiaCube(float mass, float side);
Eigen::Matrix3f inertiaSphere(float mass, float radius);
Eigen::Matrix3f inertiaBox(float mass, float a, float b, float c);
Eigen::Matrix3f inertiaCylinder(float mass, float radius, float length);

#endif