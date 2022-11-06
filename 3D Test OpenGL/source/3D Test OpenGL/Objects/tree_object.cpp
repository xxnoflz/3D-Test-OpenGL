#include "tree_object.h"

TreeObject::TreeObject(glm::vec3 start_position, glm::vec2 size, bool is_following, float following_speed, Texture& tree_texture) :
	GameObject(start_position, size, glm::vec3(size, 0.5f)), 
	m_follows(is_following), m_following_speed(following_speed), 
	m_tree_texture(tree_texture),
	m_forward(glm::vec3(0.0f, 0.0f, 1.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f))
{

}

void TreeObject::SetFollowing(bool is_following) {
	m_follows = is_following;
}

void TreeObject::UpdateFollowing(glm::vec3 to_follow, float dTime) {
	if (!m_follows)
		return;
	glm::vec3 direction{ glm::normalize(to_follow - GetPosition()) };
	float cosA{ glm::dot(direction, m_forward) };
	float sinA{ glm::length(glm::cross(m_forward, direction)) };
	float degree{ glm::degrees(std::atan2f(sinA, cosA)) };

	float negative_test{ glm::dot(m_up, glm::cross(m_forward, direction)) };
	if (negative_test < 0.0f)
		degree = -degree;
	SetDegree(degree);

	SetPosition(this->GetPosition() + (direction * dTime * m_following_speed));
}

void TreeObject::DrawTree(QuadRenderer* renderer) {
	renderer->Draw(m_tree_texture, GetPosition(), GetSize(), GetDegree(), GetRotationAxes());
}

bool TreeObject::GetFollowingStatus() {
	return m_follows;
}
