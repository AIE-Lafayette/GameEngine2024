#include "Gizmos.h"
#include <glad/glad.h>
#include <iostream>
#include "Window.h"
#include <vector>

unsigned int GameGraphics::Gizmos::m_vertexBufferID = 0;
unsigned int GameGraphics::Gizmos::m_fragBufferID = 0;
unsigned int GameGraphics::Gizmos::m_vertexArrayID = 0;
unsigned int GameGraphics::Gizmos::m_shaderProgram = 0;
char* GameGraphics::Gizmos::m_vertexShader = nullptr;
char* GameGraphics::Gizmos::m_fragShader = nullptr;

void GameGraphics::Gizmos::init()
{
	//Create a new buffer on the GPU that can store data about our objects.
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_fragBufferID);
	glGenVertexArrays(1, &m_vertexArrayID);

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

	//Move the current position being read to the end of the file.
	fseek(vertexShaderFile, 0, SEEK_END);
	//Use the current position that the file is being read at to count the size of the entire file.
	unsigned int vertexShaderSize = ftell(vertexShaderFile);
	//Reset the current position being read to be back at the beginning of the file.
	rewind(vertexShaderFile);

	//Create a new array to store the characters of the vertex shader.
	m_vertexShader = new char[vertexShaderSize + 1];
	//Set the last character to be null so that functions know when to stop.
	m_vertexShader[vertexShaderSize] = '\0';
	//Load vertex shader code.
	fread_s(m_vertexShader, sizeof(char) * vertexShaderSize + 1, 1, vertexShaderSize, vertexShaderFile);
	//Close the file so other programs can access it.
	fclose(vertexShaderFile);

	//Create a variable to store the id of the new shader.
	unsigned int vertexShader;
	//Tell opengl to create a new vertex shader and store the ID.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Pass in the code to opengl and compile it.
	glShaderSource(vertexShader, 1, &m_vertexShader, NULL);
	glCompileShader(vertexShader);

	int vertexSuccess;
	char* vertexInfoLog = new char[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);

	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
		std::cout << "Vertex shader compilation failed. \n" << vertexInfoLog << std::endl;
		delete[] vertexInfoLog;
		return;
	}

	//Load the frag shader text file.
	FILE* fragShaderFile;
	fopen_s(&fragShaderFile, "GizmoShader.frag", "rb");

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
	m_fragShader = new char[fragShaderSize + 1];
	//Set the last character to null so functions know when to stop.
	m_fragShader[fragShaderSize] = '\0';

	//Load frag shader code.
	fread_s(m_fragShader, sizeof(char) * fragShaderSize + 1, 1, fragShaderSize, fragShaderFile);
	fclose(fragShaderFile);

	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &m_fragShader, NULL);
	glCompileShader(fragShader);

	int fragSuccess;
	char* fragInfoLog = new char[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragSuccess);

	if (!fragSuccess)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, fragInfoLog);
		std::cout << "Frag shader compilation failed\n" << fragInfoLog << std::endl;
		delete[] fragInfoLog;
		return;
	}

	//Create a program to perform all of the shader logic.
	m_shaderProgram = glCreateProgram();

	//Attach the shaders to the program so it usues their code.
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragShader);
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void GameGraphics::Gizmos::drawTriangle(GameMath::Vector2 point1, GameMath::Vector2 point2, GameMath::Vector2 point3, GameMath::Vector4 color)
{
	//Convert the world positions into normalized screen space.
	point1 = GameGraphics::Window::convertToScreenPosition(point1);
	point2 = GameGraphics::Window::convertToScreenPosition(point2);
	point3 = GameGraphics::Window::convertToScreenPosition(point3);

	//Create a an array/buffer to store the vertex positions.
	float vertices[] = {
		point1.x, point1.y, 0.0f,
		point2.x, point2.y, 0.0f,
		point3.x, point3.y, 0.0f
	};

	//Bind the array that should keep track of this set of attributes.
	glBindVertexArray(m_vertexArrayID);

	//Bind the buffer generated earlier to store the vertex data.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	//Create a pointer to the attribute that is going to set the vertex position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	//Enable the specific attribute.
	glEnableVertexAttribArray(0);

	//Get the location in the shader program for the color uniform.
	int colorLocation = glGetUniformLocation(m_shaderProgram, "color");
	//Set the uniform to be the new color value.
	glUniform4f(colorLocation, color.x, color.y, color.z, color.w);

	glUseProgram(m_shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GameGraphics::Gizmos::drawBox(GameMath::Vector2 dimensions, GameMath::Vector2 position, GameMath::Vector4 color)
{
	dimensions = GameGraphics::Window::convertToScreenPosition(dimensions);
	position = GameGraphics::Window::convertToScreenPosition(position);

	GameMath::Vector2 topRight = { position.x + dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 topLeft = { position.x - dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 bottomRight = { position.x + dimensions.x / 2, position.y - dimensions.y / 2 };
	GameMath::Vector2 bottomLeft = { position.x - dimensions.x / 2, position.y - dimensions.y / 2 };

	float vertices[] = {
		topRight.x, topRight.y, 0.0f,
		topLeft.x, topLeft.y, 0.0f,
		bottomRight.x, bottomRight.y, 0.0f,
		bottomLeft.x, bottomLeft.y, 0.0f
	};

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	int colorLocation = glGetUniformLocation(m_shaderProgram, "color");
	glUniform4f(colorLocation, color.x, color.y, color.z, color.w);

	glUseProgram(m_shaderProgram);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void GameGraphics::Gizmos::drawBoxLines(GameMath::Vector2 dimensions, GameMath::Vector2 position, GameMath::Vector4 color)
{
	dimensions = GameGraphics::Window::convertToScreenPosition(dimensions);
	position = GameGraphics::Window::convertToScreenPosition(position);

	GameMath::Vector2 topRight = { position.x + dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 topLeft = { position.x - dimensions.x / 2, position.y + dimensions.y / 2 };
	GameMath::Vector2 bottomRight = { position.x + dimensions.x / 2, position.y - dimensions.y / 2 };
	GameMath::Vector2 bottomLeft = { position.x - dimensions.x / 2, position.y - dimensions.y / 2 };

	float vertices[] = {
		topRight.x, topRight.y, 0.0f,
		topLeft.x, topLeft.y, 0.0f,
		bottomLeft.x, bottomLeft.y, 0.0f,
		bottomRight.x, bottomRight.y, 0.0f
	};

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	int colorLocation = glGetUniformLocation(m_shaderProgram, "color");
	glUniform4f(colorLocation, color.x, color.y, color.z, color.w);

	glUseProgram(m_shaderProgram);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void GameGraphics::Gizmos::drawCircle(GameMath::Vector2 position, float radius, int vertices, GameMath::Vector4 color)
{
	//The total amount of vertices is going to increase by two to include the origin and one more to close the loop.
	int size = vertices + 2;

	std::vector<GameMath::Vector2> vertexPositions;
	std::vector<float> vertexList;

	//Store pi since there isn't an easy way to get a constant.
	float pi = 3.14159265359f;
	//Find the amount the angle of the circle will increase between each vertex.
	float angleIncrease = pi * 2 / vertices;
	float angle = 0;
	//Place a vertex at the circles center point so the circle fills correctly.
	GameMath::Vector2 vertexPosition = GameGraphics::Window::convertToScreenPosition(position);
	vertexPositions.push_back(vertexPosition);

	//Loop to find the rest of the vertex screen locations.
	for (int i = 0; i < size; i++)
	{
		//Find the position of the vertex by adding the current direction vector to the position.
		vertexPosition = position + (GameMath::Vector2{ cos(angle), sin(angle) } * radius);
		vertexPosition = GameGraphics::Window::convertToScreenPosition(vertexPosition);

		//Add the new vertex position to the list and increase the angle to find the next.
		vertexPositions.push_back(vertexPosition);
		angle += angleIncrease;
	}

	//Loop to collect all of the individual vertex coordinates to pass off to opengl.
	for (int i = 0; i < size; i++)
	{
		vertexList.push_back(vertexPositions[i].x);
		vertexList.push_back(vertexPositions[i].y);
		vertexList.push_back(0);
	}

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexList.size(), &vertexList[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	int colorLocation = glGetUniformLocation(m_shaderProgram, "color");
	glUniform4f(colorLocation, color.x, color.y, color.z, color.w);

	glUseProgram(m_shaderProgram);
	glDrawArrays(GL_TRIANGLE_FAN, 0, size);

	vertexList.clear();
	vertexPositions.clear();
}

void GameGraphics::Gizmos::drawCircleLines(GameMath::Vector2 position, float radius, int vertices, GameMath::Vector4 color)
{//The total amount of vertices is going to increase by two to include the origin and one more to close the loop.
	int size = vertices + 2;

	std::vector<GameMath::Vector2> vertexPositions;
	std::vector<float> vertexList;

	//Store pi since there isn't an easy way to get a constant.
	float pi = 3.14159265359f;
	//Find the amount the angle of the circle will increase between each vertex.
	float angleIncrease = pi * 2 / vertices;
	float angle = 0;

	GameMath::Vector2 vertexPosition;

	//Loop to find the rest of the vertex screen locations.
	for (int i = 0; i < size; i++)
	{
		//Find the position of the vertex by adding the current direction vector to the position.
		vertexPosition = position + (GameMath::Vector2{ cos(angle), sin(angle) } *radius);
		vertexPosition = GameGraphics::Window::convertToScreenPosition(vertexPosition);

		//Add the new vertex position to the list and increase the angle to find the next.
		vertexPositions.push_back(vertexPosition);
		angle += angleIncrease;
	}

	//Loop to collect all of the individual vertex coordinates to pass off to opengl.
	for (int i = 0; i < size; i++)
	{
		vertexList.push_back(vertexPositions[i].x);
		vertexList.push_back(vertexPositions[i].y);
		vertexList.push_back(0);
	}

	glBindVertexArray(m_vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexList.size(), &vertexList[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	int colorLocation = glGetUniformLocation(m_shaderProgram, "color");
	glUniform4f(colorLocation, color.x, color.y, color.z, color.w);

	glUseProgram(m_shaderProgram);
	glDrawArrays(GL_LINE_LOOP, 0, size);

	vertexList.clear();
	vertexPositions.clear();
}
