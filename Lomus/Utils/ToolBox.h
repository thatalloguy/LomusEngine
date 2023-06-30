#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <math.h>

glm::vec3 convertToVec3(glm::quat quat) {
	glm::vec3 value;
	value.x = atan2(2 * (quat.w * quat.x + quat.y * quat.z), 1 - 2 * (quat.x * quat.x + quat.y * quat.y));
	value.y = asin(2 * (quat.w * quat.y - quat.z * quat.x));
	value.z = atan2(2 * (quat.w * quat.z + quat.x * quat.y), 1 - 2 * (quat.y * quat.y + quat.z * quat.z));
	return value;
}

glm::quat convertToQuaturnion(glm::vec3 rotation) {
	glm::quat quat;
	float c1 = cos(rotation.z / 2);
	float s1 = sin(rotation.z / 2);
	float c2 = cos(rotation.x / 2);
	float s2 = sin(rotation.x / 2);
	float c3 = cos(rotation.y / 2);
	float s3 = sin(rotation.y / 2);
	float c1c2 = c1 * c2;
	float s1s2 = s1 * s2;
	quat.w = c1c2 * c3 - s1s2 * s3;
	quat.x = c1c2 * s3 + s1s2 * c3;
	quat.y = s1 * c2 * c3 + c1 * s2 * s3;
	quat.z = c1 * s2 * c3 - s1 * c2 * s3;
	return quat;
}

