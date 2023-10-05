#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GameEngine2024/Engine.h>
#include "Gizmos.h"

void error_callback(int error, const char* description)
{
	std::cout << description << std::endl;
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GameGraphics::Window::Window(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw library" << std::endl;
		return;
	}

	m_height = height;
	m_width = width;
	m_title = title;

	glfwSetErrorCallback(error_callback);
}

bool GameGraphics::Window::getShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

int GameGraphics::Window::getFrameRate()
{
	return 0;
}

void GameGraphics::Window::setTargetFrameRate(int fps)
{
	
}

void GameGraphics::Window::open()
{
	//Create a new window using glfw and store the context.
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	//If glfw wasn't able to create the window log the error and stop glfw.
	if (!m_window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return;
	}

	//Tell glfw to focus on the window we made.
	glfwMakeContextCurrent(m_window);
	//Set a function to be called whenever the window should be resized.
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	//Bind the open gl functions using the address of the glfw process.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, m_width, m_height);

	GameGraphics::Gizmos::init();
}

void GameGraphics::Window::beginDrawing()
{
	//Setting the color to draw over the screen
	glClearColor(0, 0, 0, 0);
	//Draw over all elements on the screen
	glClear(GL_COLOR_BUFFER_BIT);

	GameGraphics::Gizmos::drawTriangle({ -200,0 }, { 200, 0 }, { 0,200 }, {0.5f, 0.5f, 0.0f, 1});
}

void GameGraphics::Window::endDrawing()
{
	//Swaps the current data being used to draw to the screen.
	glfwSwapBuffers(m_window);
	//Checks for and calls events for the window and input
	glfwPollEvents();
}

void GameGraphics::Window::close()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GameMath::Vector2 GameGraphics::Window::convertToScreenPosition(GameMath::Vector2 position)
{
	float halfWidth = (float)GameEngine::Engine::getWindow()->getWidth() / 2;
	float halfHeight = (float)GameEngine::Engine::getWindow()->getHeight() / 2;

	position.x = position.x / halfWidth;
	position.y = position.y / halfHeight;

	return position;
}
