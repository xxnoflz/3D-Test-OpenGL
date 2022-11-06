#include "collision_engine.h"

bool CollisionEngine::SATCollision(GameObject* first_object, GameObject* second_object) {
	std::vector<std::vector<glm::vec3>> first_box_points{ GeneratePointsForQuad(first_object) };
	std::vector<std::vector<glm::vec3>> second_box_points{ GeneratePointsForQuad(second_object) };

	std::vector<glm::vec3> first_object_normals{ GetNormals(first_object, first_box_points) };
	std::vector<glm::vec3> second_object_normals{ GetNormals(second_object, second_box_points) };

	std::vector<glm::vec3> axes_to_check{
		first_object_normals[0],
		first_object_normals[1],
		first_object_normals[2],
		second_object_normals[0],
		second_object_normals[1],
		second_object_normals[2]
	};

	for (int axes_iterator{}; axes_iterator < axes_to_check.size(); ++axes_iterator) {
		Axis first_projection{ ProjectOntoAxis(first_box_points, axes_to_check[axes_iterator]) };
		Axis second_projection{ ProjectOntoAxis(second_box_points, axes_to_check[axes_iterator]) };
			if (first_projection.maxProjection < second_projection.minProjection ||
				second_projection.maxProjection < first_projection.minProjection)
					return false;
	}
	return true;
}
 
std::vector<std::vector<glm::vec3>> CollisionEngine::GeneratePointsForQuad(GameObject* object) {
	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, object->GetPosition());
	if(object->GetRotationAxes() != glm::vec3(0.0f))
		model = glm::rotate(model, glm::radians(object->GetDegree()), object->GetRotationAxes());
	model = glm::scale(model, object->GetColliderBoxSize());
	std::vector<std::vector<glm::vec4>> vertices{
		//FRONT
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	0.0f,	1.0f)
		},
		//LEFT
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	1.0f,	1.0f),
			glm::vec4(0.0f,		0.0f,	1.0f,	1.0f)
		},
		//RIGHT
		{
			glm::vec4(1.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	1.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	1.0f,	1.0f)
		},
		//BACK
		{
			glm::vec4(0.0f,		0.0f,	1.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	1.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	1.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	1.0f,	1.0f)
		}
};
	std::vector<std::vector<glm::vec3>> points(4);
	for (int row_iterator{}; row_iterator < vertices.size(); ++row_iterator) {
		for (int vertex_iterator{}; vertex_iterator < vertices[row_iterator].size(); ++vertex_iterator) {
			vertices[row_iterator][vertex_iterator] = model * vertices[row_iterator][vertex_iterator];

			points[row_iterator].push_back(glm::vec3(vertices[row_iterator][vertex_iterator]));
		}
	}
	return points;
}

std::vector<glm::vec3> CollisionEngine::GetNormals(GameObject* object, std::vector<std::vector<glm::vec3>>& object_points) {
	std::vector<std::vector<glm::vec3>> points{ GeneratePointsForQuadNormals(object) };
	std::vector<glm::vec3> normals;
	for (int row_iterator{}; row_iterator < points.size(); ++row_iterator) {
			glm::vec3 first_vector{ points[row_iterator][1] - points[row_iterator][0] };	//Second element minus first
			glm::vec3 second_vector{ points[row_iterator][2] - points[row_iterator][0] };	//Third element minus first

			normals.push_back(glm::normalize((glm::cross(first_vector, second_vector))));
	}

	return normals;
}

std::vector<std::vector<glm::vec3>> CollisionEngine::GeneratePointsForQuadNormals(GameObject* object) {
	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, object->GetPosition());
	if (object->GetRotationAxes() != glm::vec3(0.0f))
		model = glm::rotate(model, glm::radians(object->GetDegree()), object->GetRotationAxes());
	model = glm::scale(model, object->GetColliderBoxSize());
	std::vector<std::vector<glm::vec4>> vertices{
		//Right-Left Axis
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	1.0f,	1.0f)
		},
		//Up-Down Axis
		{
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	1.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f)
		},
		//Front-Back Axis
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f)
		}
	};

	std::vector<std::vector<glm::vec3>> points(3);

	for (int row_iterator{}; row_iterator < vertices.size(); ++row_iterator) {
		for (int point_iterator{}; point_iterator < vertices[row_iterator].size(); ++point_iterator) {
			vertices[row_iterator][point_iterator] = model * vertices[row_iterator][point_iterator];

			points[row_iterator].push_back(glm::vec3(vertices[row_iterator][point_iterator]));
		}
	}
	return points;
}


CollisionEngine::Axis CollisionEngine::ProjectOntoAxis(std::vector<std::vector<glm::vec3>>& points, glm::vec3& normal) {
	float minProjection{ glm::dot(points[0][0], normal) };
	float maxProjection{ minProjection };

	for (int row_iterator{}; row_iterator < points.size(); ++row_iterator) {
		for (int point_iterator{}; point_iterator < points[row_iterator].size(); ++point_iterator) {
			float currentProjection{ glm::dot(points[row_iterator][point_iterator], normal) };

			if (minProjection > currentProjection)
				minProjection = currentProjection;
			if (currentProjection > maxProjection)
				maxProjection = currentProjection;
		}
	}
	return { minProjection, maxProjection };
}
