#include "3d_test.h"

test::TEST_3D::TEST_3D(uint32_t window_width, uint32_t window_height) : 
	m_window_width(window_width), m_window_height(window_height), m_time()
{
	this->Init();
}


void test::TEST_3D::Init() {
	this->InitOpenGL();

	ResourceManager::CreateShader("source/3D Test OpenGL/Shaders/vertex.glsl", "source/3D Test OpenGL/Shaders/fragment.glsl", "quadShader");
	glm::mat4 projection{ glm::perspective(glm::radians(45.0f), (float)this->m_window_width / (float)this->m_window_height, 0.1f, 100.0f) };
	ResourceManager::GetShader("quadShader").use();
	ResourceManager::GetShader("quadShader").SetMat4("projection", projection);

	ResourceManager::CreateTexture("source/3D Test OpenGL/Textures/texture.jpg", "mystical_tree");
	ResourceManager::CreateTexture("source/3D Test OpenGL/Textures/texture_floor.jpg", "floor_texture");

	m_player = new PlayerObject(glm::vec3(0.0f, 0.0f, 5.0f));

	m_quadRender = new QuadRenderer(ResourceManager::GetShader("quadShader"));

	m_sound_engine = irrklang::createIrrKlangDevice();

	m_tree_object = new TreeObject(glm::vec3(0.0f), glm::vec2(2.0f), false, 6.0f, ResourceManager::GetTexture("mystical_tree"));
	m_tree_object->SetRotationAxes(glm::vec3(0.0f, 1.0f, 0.0f));
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	test::TEST_3D* main_func{ static_cast<test::TEST_3D*>(glfwGetWindowUserPointer(window)) };
	main_func->GetPlayerObject()->UpdateCameraDirection((float)xPos, (float)yPos);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glm::mat4 new_projection{ glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f) };
	ResourceManager::GetShader("quadShader").use();
	ResourceManager::GetShader("quadShader").SetMat4("projection", new_projection);
}

void test::TEST_3D::InitOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->m_window = glfwCreateWindow(this->m_window_width, this->m_window_height, "3D Test", nullptr, nullptr);
	glfwMakeContextCurrent(this->m_window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	glViewport(0, 0, this->m_window_width, this->m_window_height);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsLight();
}

void test::TEST_3D::KeyboardHandling() {
	if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(PlayerObject::W, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(PlayerObject::S, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(PlayerObject::A, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(PlayerObject::D, m_time.deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(PlayerObject::SPACE, m_time.deltaTime);

	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
		m_tree_object->SetFollowing(!m_tree_object->GetFollowingStatus());
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}


PlayerObject* test::TEST_3D::GetPlayerObject() {
	return m_player;
}

test::TimeHandler& test::TEST_3D::GetTimeHandler() {
	return m_time;
}


void test::TEST_3D::UpdateTime() {
	m_time.currentFrame = (float)glfwGetTime();
	m_time.deltaTime = m_time.currentFrame - m_time.lastFrame;
	m_time.lastFrame = m_time.currentFrame;
}

void test::TEST_3D::Update() {
	if (CollisionEngine::SATCollision(m_player, m_tree_object))
		glfwSetWindowShouldClose(m_window, true);
	UpdateTime();
	KeyboardHandling();
	m_tree_object->UpdateFollowing(m_player->GetPosition(), m_time.deltaTime);
	m_player->Update(m_time.deltaTime);
}

void test::TEST_3D::StartDebugMenu() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void test::TEST_3D::EndDebugMenu() {
	ImGui::Begin("Debug Menu");
	ImGui::SetWindowSize(ImVec2(500.0f, 150.0f));
	ImGui::Text("Player Position: %f, %f, %f", m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	ImGui::Text("Tree Position: %f, %f, %f", m_tree_object->GetPosition().x, m_tree_object->GetPosition().y, m_tree_object->GetPosition().z);
	ImGui::Text("Following Status: %i", m_tree_object->GetFollowingStatus());
	//ImGui::Text("Text: %i", CollisionEngine::SATCollision(m_player, m_tree_object));
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void test::TEST_3D::run() {
	m_sound_engine->play2D("source/3D Test OpenGL/Music/ost.mp3", true);
	while (!glfwWindowShouldClose(this->m_window)) {
		Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		StartDebugMenu();

		m_tree_object->DrawTree(m_quadRender);
		m_quadRender->Draw(ResourceManager::GetTexture("floor_texture"), glm::vec3(-50.0f, 0.0f, -50.0f), glm::vec2(100.0f), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		
		EndDebugMenu();

		glfwPollEvents();
		glfwSwapBuffers(this->m_window);
	}
	glfwTerminate();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}