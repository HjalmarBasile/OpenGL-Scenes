#pragma once

#include <memory>
#include "Scene.h"
#include "Camera.h"
#include "primitives/Cube.h"
#include <GLFW/glfw3.h>

namespace scene {

	class SceneCamera : public AbstractScene
	{
	public:
		static constexpr const char* name = "Camera";
		SceneCamera(GLFWwindow* window, int windowWidth, int windowHeight);
		~SceneCamera();

		std::string GetName() const override;

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		void processUserInput(float deltaTime);

		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static constexpr int TOTAL_CUBES = 13;
		static std::unique_ptr<Camera> s_Camera;
		float m_CameraSpeed;

		GLFWwindow* m_Window;
		std::unique_ptr<Cube> m_Cube;

		const glm::vec3 m_CubesPositions[TOTAL_CUBES] = {
			/* H */
			glm::vec3(-3.0f, -1.0f, 0.0f),
			glm::vec3(-3.0f,  0.0f, 0.0f),
			glm::vec3(-3.0f,  1.0f, 0.0f),
			glm::vec3(-2.0f,  0.0f, 0.0f),
			glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(-1.0f,  0.0f, 0.0f),
			glm::vec3(-1.0f,  1.0f, 0.0f),

			/* J */
			glm::vec3( 1.0f, -1.0f, 0.0f),
			glm::vec3( 1.0f,  1.0f, 0.0f),
			glm::vec3( 2.0f, -1.0f, 0.0f),
			glm::vec3( 2.0f,  0.0f, 0.0f),
			glm::vec3( 2.0f,  1.0f, 0.0f),
			glm::vec3( 3.0f,  1.0f, 0.0f)
		};

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj;
		glm::mat4 m_MVP;
	};

}
