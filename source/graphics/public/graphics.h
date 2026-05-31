#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "../../app.h"
#include "shader.h"

struct Vertex
{
	Vertex(float x, float y) : position(x, y) {}
	glm::vec2 position;
};

class Graphics
{
public:
	static int InitOpenGL()
	{
		// Initialize GLFW, tell it we are using OpenGL 4.3 Core
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Procedural Maze Generator", NULL, NULL);

		// Handle Errors if window fails to be created
		if (Window == NULL)
		{
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(Window);

		// Make sure GLAD is initialized so that it can manage OpenGL Function Pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		// Initialize the viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		// Set a callback functions for resizing the window and detecting key inputs
		glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);
		glfwSetKeyCallback(Window, KeyCallback);
		
		// Enable depth testing and gamma correction
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_FRAMEBUFFER_SRGB);

		return 1;
	}

	static void InitShaders()
	{
		GridShader.SetupShader("shaders/vertex.vert", "shaders/grid.frag");
		glGenVertexArrays(1, &GridVAO);
		glGenBuffers(1, &GridVBO);
		glBindVertexArray(GridVAO);
		glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
		glBufferData(GL_ARRAY_BUFFER, GridVertices.size() * sizeof(Vertex), GridVertices.data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		ShortestPathShader.SetupShader("shaders/vertex.vert", "shaders/path.frag");
		glGenVertexArrays(1, &ShortestPathVAO);
		glGenBuffers(1, &ShortestPathVBO);
		glBindVertexArray(ShortestPathVAO);
		glBindBuffer(GL_ARRAY_BUFFER, ShortestPathVBO);
		glBufferData(GL_ARRAY_BUFFER, ShortestPathVertices.size() * sizeof(Vertex), ShortestPathVertices.data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		LongestPathShader.SetupShader("shaders/vertex.vert", "shaders/path.frag");
		glGenVertexArrays(1, &LongestPathVAO);
		glGenBuffers(1, &LongestPathVBO);
		glBindVertexArray(LongestPathVAO);
		glBindBuffer(GL_ARRAY_BUFFER, LongestPathVBO);
		glBufferData(GL_ARRAY_BUFFER, LongestPathVertices.size() * sizeof(Vertex), LongestPathVertices.data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}

	static void UpdateLoop()
	{
		while (!glfwWindowShouldClose(Window))
		{
			// Render stuff here... 
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			DrawGrid();

			if (bShouldDrawLongestPath) DrawLongestPath();
			if (bShouldDrawShortestPath) DrawShortestPath();

			// Check and call events/ callback functions, then swap the buffer
			glfwPollEvents();
			glfwSwapBuffers(Window);
		}
	}

	static void DrawGrid()
	{
		GridShader.use();
		GridShader.setFloat("uTime", static_cast<float>(glfwGetTime()));
		glBindVertexArray(GridVAO);
		glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
		glBufferData(GL_ARRAY_BUFFER, GridVertices.size() * sizeof(Vertex), GridVertices.data(), GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(GridVertices.size()));
	}

	static void DrawShortestPath()
	{
		ShortestPathShader.use();
		ShortestPathShader.setFloat("uTime", static_cast<float>(glfwGetTime()));
		ShortestPathShader.setBool("uIsShortestPath", true);
		glBindVertexArray(ShortestPathVAO);
		glBindBuffer(GL_ARRAY_BUFFER, ShortestPathVBO);
		glBufferData(GL_ARRAY_BUFFER, ShortestPathVertices.size() * sizeof(Vertex), ShortestPathVertices.data(), GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(ShortestPathVertices.size()));
	}

	static void DrawLongestPath()
	{
		LongestPathShader.use();
		LongestPathShader.setFloat("uTime", static_cast<float>(glfwGetTime()));
		LongestPathShader.setBool("uIsShortestPath", false);
		glBindVertexArray(LongestPathVAO);
		glBindBuffer(GL_ARRAY_BUFFER, LongestPathVBO);
		glBufferData(GL_ARRAY_BUFFER, LongestPathVertices.size() * sizeof(Vertex), LongestPathVertices.data(), GL_DYNAMIC_DRAW);
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(LongestPathVertices.size()));
	}

	static void AddGridLine(float x1, float y1, float x2, float y2)
	{
		AddLine(x1, y1, x2, y2, GridVertices);
	}

	static void AddShortestPathLine(float x1, float y1, float x2, float y2)
	{
		AddLine(x1, y1, x2, y2, ShortestPathVertices);
	}

	static void AddLongestPathLine(float x1, float y1, float x2, float y2)
	{
		AddLine(x1, y1, x2, y2, LongestPathVertices);
	}

	static void CleanUp()
	{
		glDeleteVertexArrays(1, &GridVAO);
		glDeleteBuffers(1, &GridVBO);
		glDeleteVertexArrays(1, &ShortestPathVAO);
		glDeleteBuffers(1, &ShortestPathVBO);
		glDeleteVertexArrays(1, &LongestPathVAO);
		glDeleteBuffers(1, &LongestPathVBO);
		glfwDestroyWindow(Window);
		glfwTerminate();
	}

public:
	static const unsigned int SCR_WIDTH = 720;
	static const unsigned int SCR_HEIGHT = 720;
	inline static GLFWwindow* Window = nullptr;

	inline static float Rows = -1;
	inline static float Columns = -1;

	inline static bool bShouldDrawShortestPath = false;
	inline static bool bShouldDrawLongestPath = false;

	inline static unsigned int GridVAO = 0;
	inline static unsigned int GridVBO = 0;
	inline static unsigned int ShortestPathVAO = 0;
	inline static unsigned int ShortestPathVBO = 0;
	inline static unsigned int LongestPathVAO = 0;
	inline static unsigned int LongestPathVBO = 0;

	inline static std::vector<Vertex> GridVertices;
	inline static std::vector<Vertex> ShortestPathVertices;
	inline static std::vector<Vertex> LongestPathVertices;

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // ESC
			glfwSetWindowShouldClose(window, true);

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) // SPACEBAR
		{
			App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
			app->GenerateMaze();
		}
	}

	// Converts from Maze Space into normalized Clip Space in the X dimension
	static float NormalizeX(float x)
	{
		return MinClip + (x / Columns) * (MaxClip - MinClip);
	}

	// Converts from Maze Space into normalized Clip Space in the Y dimension
	static float NormalizeY(float y)
	{
		return MaxClip - (y / Rows) * (MaxClip - MinClip);
	}

	static void AddLine(float x1, float y1, float x2, float y2, std::vector<Vertex>& vertices)
	{
		vertices.emplace_back(NormalizeX(x1), NormalizeY(y1));
		vertices.emplace_back(NormalizeX(x2), NormalizeY(y2));
	}

private:
	inline static Shader GridShader;
	inline static Shader ShortestPathShader;
	inline static Shader LongestPathShader;
	static constexpr float MinClip = -0.9f; // Maze bounds cannot extend past -0.9 in clipspace XY dimensions
	static constexpr float MaxClip = 0.9f; // Maze bounds cannot extend past +0.9 in clipspace XY dimensions
};