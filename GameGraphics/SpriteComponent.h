#pragma once
#include "GameEngine2024/Component.h"
#include "Shader.h"
#include <GameMath/Vector4.h>

namespace GameGraphics
{
	class SpriteComponent : public GameEngine::Component
	{
	public:
		SpriteComponent();
		SpriteComponent(const char* texturePath);
		SpriteComponent(const char* texturePath, const char* vertexShader, const char* fragShader);

		GameMath::Vector4 getColor() { return m_color; }

		void setColor(GameMath::Vector4 color) { m_color = color; }
		void setTexture(const char* texturePath);

		void draw() override;

	private:
		const char* m_texturePath;
		GameGraphics::Shader* m_spriteShader;
		GameMath::Vector4 m_color;
		unsigned int m_textureID;
	};
}
