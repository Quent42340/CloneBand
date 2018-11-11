/*
 * =====================================================================================
 *
 *       Filename:  Transform.cpp
 *
 *    Description:
 *
 *        Created:  11/11/2018 17:39:55
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

#include "Transform.hpp"

const Transform Transform::Identity;

Transform::Transform(const glm::mat4 &matrix) {
	m_matrix = matrix;
}

Transform& Transform::combine(const Transform& transform) {
	m_matrix *= transform.m_matrix;
	return *this;
}

Transform& Transform::translate(float x, float y, float z) {
	m_matrix = glm::translate(m_matrix, {x, y, z});
	return *this;
}

Transform& Transform::rotate(float angle, const Vector3f& axis) {
	float rotationAngle = angle * RADIANS_PER_DEGREES;
	m_matrix = glm::rotate(m_matrix, rotationAngle, {axis.x, axis.y, axis.z});
	return *this;
}

Transform& Transform::scale(float scaleX, float scaleY, float scaleZ) {
	m_matrix = glm::scale(m_matrix, {scaleX, scaleY, scaleZ});
	return *this;
}

const float* Transform::getMatrix() const {
	return glm::value_ptr(m_matrix);
}

Transform Transform::getInverse() const {
	return glm::inverse(m_matrix);
}

Transform Transform::getTranspose() const {
	return glm::transpose(m_matrix);
}

Transform operator *(const Transform& left, const Transform &right) {
	return Transform(left).combine(right);
}

Transform& operator *=(Transform &left, const Transform &right) {
	return left.combine(right);
}

