#include "Engine.h"
#include <chrono>
#include "Scene.h"
#include "GameGraphics/Window.h"

GameEngine::Scene* GameEngine::Engine::m_currentScene = nullptr;
double GameEngine::Engine::m_deltaTime = 0;
double GameEngine::Engine::m_fixedTimeStep = 0.01f;

GameGraphics::Window* GameEngine::Engine::m_window = nullptr;

bool GameEngine::Engine::getApplicationShouldClose()
{
	return m_window->getShouldClose();
}

void GameEngine::Engine::closeApplication()
{
	m_window->close();
}

void GameEngine::Engine::run()
{
	double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double deltaTime = 0;
	double accumulatedTime = 0;

	m_window = new GameGraphics::Window(800, 800, "Test Application");
	m_window->open();

	start();

	while (!getApplicationShouldClose())
	{
		double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		deltaTime = currentTime - lastTime;

		lastTime = currentTime;

		accumulatedTime += deltaTime / 1000;

		m_deltaTime = deltaTime / 1000;

		update(m_deltaTime);

		while (accumulatedTime >= m_fixedTimeStep)
		{
			accumulatedTime -= m_fixedTimeStep;
			fixedUpdate(getTimeStep());
		}

		m_window->beginDrawing();
		draw();
		m_window->endDrawing();

	}

	end();

	m_window->close();
}

void GameEngine::Engine::start()
{
	m_currentScene->start();
}

void GameEngine::Engine::update(double deltaTime)
{
	m_currentScene->update(deltaTime);
}

void GameEngine::Engine::fixedUpdate(double fixedDeltaTime)
{
	m_currentScene->fixedUpdate(fixedDeltaTime);
}

void GameEngine::Engine::draw()
{
	m_currentScene->draw();
}

void GameEngine::Engine::end()
{
	m_currentScene->end();
}
