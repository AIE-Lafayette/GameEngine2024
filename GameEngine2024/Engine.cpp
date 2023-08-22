#include "Engine.h"
#include <chrono>

void GameEngine::Engine::run()
{
	double lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double deltaTime = 0;

	start();

	while (!getApplicationShouldClose())
	{
		double currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		deltaTime = currentTime - lastTime;

		lastTime = currentTime;
		
		m_deltaTime = deltaTime / 1000;

		update(m_deltaTime);
		draw();
	}

	end();
}

void GameEngine::Engine::start()
{
}
