#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

GameGraphics::Shader::Shader(const char* vertexPath, const char* fragPath)
{
	//Create a new buffer on the GPU that can store data about our objects.
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_fragBufferID);
	glGenVertexArrays(1, &m_vertexArrayID);

	//Open up the file that contains the vertex shader.
	FILE* vertexShaderFile;
	fopen_s(&vertexShaderFile, vertexPath, "rb");

	//If the file pointer is null...
	if (!vertexShaderFile)
	{
		//...log the problem and exit the function.
		std::cout << "Could not open vertex shader file." << std::endl;
		return;
	}

	//Move the current position being read to the end of the file.
	fseek(vertexShaderFile, 0, SEEK_END);
	//Use the current position that the file is being read at to count the size of the entire file.
	unsigned int vertexShaderSize = ftell(vertexShaderFile);
	//Reset the current position being read to be back at the beginning of the file.
	rewind(vertexShaderFile);

	//Create a new array to store the characters of the vertex shader.
	char* vertexShader = new char[vertexShaderSize + 1];
	//Set the last character to be null so that functions know when to stop.
	vertexShader[vertexShaderSize] = '\0';
	//Load vertex shader code.
	fread_s(vertexShader, sizeof(char) * vertexShaderSize + 1, 1, vertexShaderSize, vertexShaderFile);
	//Close the file so other programs can access it.
	fclose(vertexShaderFile);

	//Create a variable to store the id of the new shader.
	unsigned int vertexShaderID;
	//Tell opengl to create a new vertex shader and store the ID.
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	//Pass in the code to opengl and compile it.
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	int vertexSuccess;
	char* vertexInfoLog = new char[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexSuccess);

	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, vertexInfoLog);
		std::cout << "Vertex shader compilation failed. \n" << vertexInfoLog << std::endl;
		delete[] vertexInfoLog;
		return;
	}

	//Load the frag shader text file.
	FILE* fragShaderFile;
	fopen_s(&fragShaderFile, fragPath, "rb");

	//If the file wasn't loaded...
	if (!fragShaderFile)
	{
		//...log the error message.
		std::cout << "Could not open frag shader file." << std::endl;
		return;
	}

	//Move the current position being read to the end of the file.
	fseek(fragShaderFile, 0, SEEK_END);
	//Use the current position that the file is being read at to get the amount of characters.
	unsigned int fragShaderSize = ftell(fragShaderFile);
	//Reset the position to be at the beginning of the file so we can load properly.
	rewind(fragShaderFile);

	//Create a new array to store the characters of the frag shader.
	char* fragShader = new char[fragShaderSize + 1];
	//Set the last character to null so functions know when to stop.
	fragShader[fragShaderSize] = '\0';

	//Load frag shader code.
	fread_s(fragShader, sizeof(char) * fragShaderSize + 1, 1, fragShaderSize, fragShaderFile);
	fclose(fragShaderFile);

	unsigned int fragShaderID;
	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShader, NULL);
	glCompileShader(fragShaderID);

	int fragSuccess;
	char* fragInfoLog = new char[512];
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &fragSuccess);

	if (!fragSuccess)
	{
		glGetShaderInfoLog(fragShaderID, 512, NULL, fragInfoLog);
		std::cout << "Frag shader compilation failed\n" << fragInfoLog << std::endl;
		delete[] fragInfoLog;
		return;
	}

	//Create a program to perform all of the shader logic.
	m_shaderProgram = glCreateProgram();

	//Attach the shaders to the program so it usues their code.
	glAttachShader(m_shaderProgram, vertexShaderID);
	glAttachShader(m_shaderProgram, fragShaderID);
	//Links the shaders together by matching the input with the outputs.
	glLinkProgram(m_shaderProgram);

	//Log the results of linking and print when something is wrong.
	int linkSuccess;
	char* linkInfoLog = new char[512];

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linkSuccess);

	if (!linkSuccess)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, linkInfoLog);
		std::cout << "Program linking failed.\n" << linkInfoLog << std::endl;
		delete[] linkInfoLog;
		return;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);

	delete[] vertexShader;
	delete[] fragShader;
	delete[] linkInfoLog;
}

void GameGraphics::Shader::use()
{
	glUseProgram(m_shaderProgram);
}

void GameGraphics::Shader::setBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), value);
}

void GameGraphics::Shader::setInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), value);
}

void GameGraphics::Shader::setFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name), value);
}

void GameGraphics::Shader::setVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_shaderProgram, name), x, y);
}

void GameGraphics::Shader::setVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_shaderProgram, name), x, y, z, w);
}
