#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utilities/resource_manager.h"

class Camera {
public:
	Camera(const glm::vec3& cameraPosition, const glm::vec3& cameraFront);

	void UpdateCamera(float new_cursor_x, float new_cursor_y);
	void UpdateMatrix();

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
private:
	float m_cursor_x;
	float m_cursor_y;

	float m_pitch;
	float m_yaw;

	glm::mat4 m_view_matrix;

	void UpdateCameraDirection();
};