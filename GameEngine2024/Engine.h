#pragma once

namespace GameGraphics
{
	class Window;
}

namespace GameEngine
{
	class Scene;

	class Engine
	{
	public:
		Engine() {}

		static double getDeltaTime() { return m_deltaTime; }

		static double getTimeStep() { return m_fixedTimeStep; }
		static void setTimeStep(float time) { m_fixedTimeStep = time; }

		static void setCurrentScene(Scene* scene) { m_currentScene = scene; }
		static Scene* getCurrentScene() { return m_currentScene; }

		static bool getApplicationShouldClose();
		static void closeApplication();

		static GameGraphics::Window* getWindow() { return m_windowWrapper; }

		void run();

	private:
		void start();
		void update(double deltaTime);
		void fixedUpdate(double fixedDeltaTime);
		void draw();
		void end();

	private:
		static double m_deltaTime;
		static double m_fixedTimeStep;
		static Scene* m_currentScene;
		static GameGraphics::Window* m_windowWrapper;
	};

}