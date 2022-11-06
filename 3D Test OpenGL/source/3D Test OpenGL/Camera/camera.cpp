#include "camera.h"

Camera::Camera(const glm::vec3& cameraPosition, const glm::vec3& cameraFront) :
	m_cameraPos(cameraPosition), m_cameraFront(cameraFront), m_cameraUp(0.0f, 1.0f, 0.0f),
	m_pitch(0.0f), m_yaw(-90.0f),
	m_cursor_x(), m_cursor_y()
{ 
	UpdateMatrix();
}

void Camera::UpdateCamera(float new_cursor_x, float new_cursor_y) {
	float x_diff{ new_cursor_x - m_cursor_x }; 
	float y_diff{ m_cursor_y - new_cursor_y };

	m_cursor_x = new_cursor_x; 
	m_cursor_y = new_cursor_y;

	x_diff *= 0.1f; 
	y_diff *= 0.1f;

	m_yaw += x_diff; 
	m_pitch += y_diff;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	UpdateCameraDirection();
}

void Camera::UpdateCameraDirection() {
	glm::vec3 new_direction;
	new_direction.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	new_direction.y = glm::sin(glm::radians(m_pitch));
	new_direction.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(new_direction);
	UpdateMatrix();
}

void Camera::UpdateMatrix() {
	m_view_matrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	ResourceManager::GetShader("quadShader").use();
	ResourceManager::GetShader("quadShader").SetMat4("view", m_view_matrix);
}
