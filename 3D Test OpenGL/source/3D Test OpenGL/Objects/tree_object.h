#pragma once
#include <glm/glm.hpp>
#include <cmath>

#include "game_object.h"
#include "../Render/QuadRenderer.h"
#include "../Utilities/texture.h"

class TreeObject : public GameObject{
public:
	TreeObject(glm::vec3 start_position, glm::vec2 size, bool is_following, float following_speed, Texture& tree_texture);

	void SetFollowing(bool is_following);
	void UpdateFollowing(glm::vec3 to_follow, float dTime);
	bool GetFollowingStatus();

	void DrawTree(QuadRenderer* renderer);
private:
	bool m_follows;
	float m_following_speed;

	glm::vec3 m_forward;
	glm::vec3 m_up;

	Texture m_tree_texture;
};