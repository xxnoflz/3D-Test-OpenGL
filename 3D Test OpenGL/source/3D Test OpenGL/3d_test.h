#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <irrklang/irrKlang.h>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

#include "Utilities/resource_manager.h"
#include "Utilities/collision_engine.h"
#include "Render/QuadRenderer.h"
#include "Objects/player_object.h"
#include "Objects/tree_object.h"

namespace test {
	struct TimeHandler {
		float currentFrame;
		float lastFrame;
		float deltaTime;
	};

	class TEST_3D {
	public:
		TEST_3D(uint32_t window_width, uint32_t window_height);

		void Init();
		void InitOpenGL();

		void Update();
		void UpdateTime();
		void KeyboardHandling();

		void StartDebugMenu();
		void EndDebugMenu();

		void run();

		PlayerObject* GetPlayerObject();
		TimeHandler& GetTimeHandler();
	private:
		GLFWwindow* m_window;

		uint32_t m_window_width;
		uint32_t m_window_height;

		irrklang::ISoundEngine* m_sound_engine;

		QuadRenderer* m_quadRender;

		TreeObject* m_tree_object;
		PlayerObject* m_player;
		TimeHandler m_time;
	};

}