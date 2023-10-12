#pragma once

namespace GameGraphics
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragPath);

		unsigned int getProgramID() { return m_shaderProgram; }
		unsigned int getVertexBufferID() { return m_vertexBufferID; }
		unsigned int getFragBufferID() { return m_fragBufferID; }
		unsigned int getVertexArrayID() { return m_vertexBufferID; }

		void use();

		void setBool(const char* name, bool value) const;
		void setInt(const char* name, int value) const;
		void setFloat(const char* name, float value) const;
		void setVec2(const char* name, float x, float y) const;
		void setVec4(const char* name, float x, float y, float z, float w) const;

	private:
		unsigned int m_vertexBufferID;
		unsigned int m_fragBufferID;
		unsigned int m_shaderProgram;
		unsigned int m_vertexArrayID;
	};
}
