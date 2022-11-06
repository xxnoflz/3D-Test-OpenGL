#pragma once
#include <glm/glm.hpp>

#include "game_object.h"
#include "../Camera/camera.h"

class PlayerObject : public GameObject{
public:
	enum Keys {
		W = 87,
		S = 83,
		A = 65,
		D = 68,
		SPACE = 32
	};

	PlayerObject(glm::vec3 start_position, glm::vec2 size = glm::vec2(0.5f, 2.0f));

	void UpdateCameraDirection(float xPos, float yPos);
	void UpdatePlayerPosition(int key, float dTime);

	void Update(float dTime);
private:
	Camera* m_camera;

	bool m_jumping;
	bool m_grounded;

	float m_current_jumping_speed;
	float m_constant_jump_speed;

	void ApplyGravity(float dTime);
	void UpdateJumping(float dTime);
};