#pragma once
#include <glm/glm.hpp>

class GameObject {
public:
	GameObject(glm::vec3 position, glm::vec2 size, glm::vec3 collider_box_size);

	glm::vec3& GetPosition();
	glm::vec2 GetSize() const;
	glm::vec3 GetColliderBoxSize() const;
	float GetDegree() const;
	glm::vec3 GetRotationAxes() const;

	void SetPosition(glm::vec3 new_position);
	void SetDegree(float new_degree);
	void SetRotationAxes(glm::vec3 new_rotation_axes);
private:
	glm::vec3 m_position;
	glm::vec2 m_size;
	glm::vec3 m_collider_box_size;

	float m_degree;
	glm::vec3 m_rotation_axes;
};