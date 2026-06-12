#ifndef INERTIA_H
#define INERTIA_H
#include <Eigen/Dense>
#include <string>
float readFloat(const std::string &prompt);
Eigen::Vector3f normalizeVector(float x, float y, float z);
Eigen::Matrix3f inertiaCube(float mass, float side);
Eigen::Matrix3f inertiaSphere(float mass, float radius);
Eigen::Matrix3f inertiaBox(float mass, float a, float b, float c);
Eigen::Matrix3f inertiaCylinder(float mass, float radius, float length);
Eigen::Matrix3f inertiaCone(float mass, float radius, float height);
#endif
