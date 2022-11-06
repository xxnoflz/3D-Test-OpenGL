#include "game_object.h"

GameObject::GameObject(glm::vec3 position, glm::vec2 size, glm::vec3 collider_box_size) :
	m_position(position), m_size(size), m_collider_box_size(collider_box_size), 
	m_degree(0.0f), m_rotation_axes(glm::vec3(0.0f))
{

}

glm::vec3& GameObject::GetPosition() {
	return m_position;
}

glm::vec2 GameObject::GetSize() const {
	return m_size;
}

glm::vec3 GameObject::GetColliderBoxSize() const {
	return m_collider_box_size;
}

float GameObject::GetDegree() const {
	return m_degree;
}

glm::vec3 GameObject::GetRotationAxes() const {
	return m_rotation_axes;
}

void GameObject::SetPosition(glm::vec3 new_position) {
	m_position = new_position;
}

void GameObject::SetDegree(float new_degree) {
	m_degree = new_degree;
}

void GameObject::SetRotationAxes(glm::vec3 new_rotation_axes) {
	m_rotation_axes = new_rotation_axes;
}