#version 440 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 fragTexCoord;

uniform mat3 transform;

void main()
{
	vec3 newPosition = transform * pos;

	gl_Position = vec4(newPosition, 1.0f);

	fragTexCoord = texCoord;
}