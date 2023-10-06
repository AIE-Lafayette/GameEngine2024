#pragma once
#include <GameMath/Vector2.h>
#include <GameMath/Vector4.h>

namespace GameGraphics
{
	class Gizmos
	{
	public:
		static void init();
		static void drawTriangle(GameMath::Vector2 point1, GameMath::Vector2 point2, GameMath::Vector2 point3, GameMath::Vector4 color);
		static void drawBox(GameMath::Vector2 dimensions, GameMath::Vector2 position, GameMath::Vector4 color);
		static void drawBoxLines(GameMath::Vector2 dimensions, GameMath::Vector2 position, GameMath::Vector4 color);
		static void drawCircle(GameMath::Vector2 position, float radius, int vertices, GameMath::Vector4 color);
		static void drawCircleLines(GameMath::Vector2 position, float radius, int vertices, GameMath::Vector4 color);

	private:
		static unsigned int m_vertexBufferID;
		static unsigned int m_fragBufferID;
		static char* m_vertexShader;
		static char* m_fragShader;
		static unsigned int m_shaderProgram;
		static unsigned int m_vertexArrayID;
	};
}