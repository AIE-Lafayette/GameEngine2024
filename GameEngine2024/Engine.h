#pragma once

namespace GameEngine
{
	class Engine
	{
	public:
		Engine() {}

		static double getDeltaTime() { return m_deltaTime; }

		bool getApplicationShouldClose() { return m_applicationShouldClose; }
		void setApplicationShouldClose(bool value) { m_applicationShouldClose = value; }

		void run();

	private:
		void start();
		void update(double deltaTime);
		void draw();
		void end();

	private:
		bool m_applicationShouldClose;
		static double m_deltaTime;
	};

}