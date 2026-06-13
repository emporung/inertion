/*!
 * \file inertia.h
 * \brief Header file with functions for inertia tensor calculation
 */

#ifndef INERTIA_H
#define INERTIA_H

#include <Eigen/Dense>
#include <string>

/*!
 * \brief Reads a float from console with error checking
 * \param prompt Input prompt
 * \return Entered number
 * \throw std::runtime_error On EOF
 * \throw std::invalid_argument On non-numeric input
 */
float readFloat(const std::string& prompt);

/*!
 * \brief Normalizes a vector (makes length = 1)
 * \param x X component
 * \param y Y component
 * \param z Z component
 * \return Normalized vector
 * \throw std::invalid_argument If vector length is zero
 */
Eigen::Vector3f normalizeVector(float x, float y, float z);

/*!
 * \brief Inertia tensor of a cube
 * \param mass Mass (kg)
 * \param side Side length (m)
 * \return Diagonal 3x3 matrix
 */
Eigen::Matrix3f inertiaCube(float mass, float side);

/*!
 * \brief Inertia tensor of a solid sphere
 * \param mass Mass (kg)
 * \param radius Radius (m)
 * \return Diagonal 3x3 matrix
 */
Eigen::Matrix3f inertiaSphere(float mass, float radius);

/*!
 * \brief Inertia tensor of a rectangular box
 * \param mass Mass (kg)
 * \param a Length along X (m)
 * \param b Length along Y (m)
 * \param c Length along Z (m)
 * \return Diagonal 3x3 matrix
 */
Eigen::Matrix3f inertiaBox(float mass, float a, float b, float c);

/*!
 * \brief Inertia tensor of a cylinder (oriented along X axis)
 * \param mass Mass (kg)
 * \param radius Base radius (m)
 * \param length Cylinder height (m)
 * \return Diagonal 3x3 matrix
 */
Eigen::Matrix3f inertiaCylinder(float mass, float radius, float length);

/*!
 * \brief Inertia tensor of a cone (apex up, Z axis)
 * \param mass Mass (kg)
 * \param radius Base radius (m)
 * \param height Cone height (m)
 * \return Diagonal 3x3 matrix
 */
Eigen::Matrix3f inertiaCone(float mass, float radius, float height);

#endif
