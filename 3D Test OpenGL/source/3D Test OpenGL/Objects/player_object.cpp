#include "player_object.h"

PlayerObject::PlayerObject(glm::vec3 player_position, glm::vec2 size) : 
	GameObject(player_position, size, glm::vec3(size, 0.5f)),
	m_constant_jump_speed(9.81f),
	m_jumping(false), m_current_jumping_speed(m_constant_jump_speed),
	m_grounded(true)
{
	m_camera = new Camera(player_position, glm::vec3(0.0f));
}

void PlayerObject::UpdateCameraDirection(float xPos, float yPos) {
	m_camera->UpdateCamera(xPos, yPos);
}

void PlayerObject::UpdatePlayerPosition(int key, float dTime) {
	float cameraSpeed{ 5.0f * dTime };
	float last_y_position{ GetPosition().y };
	if (key == W)
		GetPosition() += cameraSpeed * m_camera->m_cameraFront;
	else if (key == S)
		GetPosition() -= cameraSpeed * m_camera->m_cameraFront;
	else if (key == A)
		GetPosition() -= cameraSpeed * glm::normalize(glm::cross(m_camera->m_cameraFront, m_camera->m_cameraUp));
	else if (key == D)
		GetPosition() += cameraSpeed * glm::normalize(glm::cross(m_camera->m_cameraFront, m_camera->m_cameraUp));
	GetPosition().y = last_y_position;

	if (key == SPACE && m_grounded)
		m_jumping = true;
}


void PlayerObject::Update(float dTime) {
	m_camera->m_cameraPos = GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f);

	ApplyGravity(dTime);
	UpdateJumping(dTime);
	m_camera->UpdateMatrix();
}

void PlayerObject::ApplyGravity(float dTime) {
	if (m_jumping || GetPosition().y <= 0.0f) {
		m_grounded = true;
		return;
	}
	GetPosition() += -m_camera->m_cameraUp * dTime * 5.0f;

	m_grounded = false;
}

void PlayerObject::UpdateJumping(float dTime) {
	if (!m_jumping)
		return;

	GetPosition() += m_camera->m_cameraUp * dTime * m_current_jumping_speed;
	m_current_jumping_speed *= 0.90f;
	if (m_current_jumping_speed < 0.65f) {
		m_jumping = false;
		m_current_jumping_speed = m_constant_jump_speed;
	}

	m_grounded = false;
}