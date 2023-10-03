#include "Gizmos.h"
#include <glad/glad.h>
#include <iostream>

unsigned int GameGraphics::Gizmos::m_vertexBufferID = 0;
unsigned int GameGraphics::Gizmos::m_fragBufferID = 0;
char* GameGraphics::Gizmos::m_vertexShader = nullptr;
char* GameGraphics::Gizmos::m_fragShader = nullptr;

void GameGraphics::Gizmos::init()
{
	//Create a new buffer on the GPU that can store data about our objects.
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_fragBufferID);

	//Open up the file that contains the vertex shader.
	FILE* vertexShaderFile;
	fopen_s(&vertexShaderFile, "GizmoShader.vert", "rb");

	//If the file pointer is null...
	if (!vertexShaderFile)
	{
		//...log the problem and exit the function.
		std::cout << "Could not open vertex shader file." << std::endl;
		return;
	}


}