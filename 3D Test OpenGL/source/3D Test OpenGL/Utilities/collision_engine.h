#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "../Objects/game_object.h"

class CollisionEngine {
public:
	struct Axis {
		float minProjection;
		float maxProjection;
	};
	static bool SATCollision(GameObject* first_object, GameObject* second_object);
private:
	static std::vector<std::vector<glm::vec3>> GeneratePointsForQuad(GameObject* object);
	static std::vector<std::vector<glm::vec3>> GeneratePointsForQuadNormals(GameObject* object);
	static std::vector<glm::vec3> GetNormals(GameObject* object, std::vector<std::vector<glm::vec3>>& object_points);
	static Axis ProjectOntoAxis(std::vector<std::vector<glm::vec3>>& points, glm::vec3& normal);
};