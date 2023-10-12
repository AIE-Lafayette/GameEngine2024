#version 440 core

out vec4 FragColor;
in vec2 fragTexCoord;
uniform sampler2D sampleTexture;

void main()
{
	FragColor = texture(sampleTexture, fragTexCoord);
}