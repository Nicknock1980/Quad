#pragma once
#include <glew.h>
#include <glfw3.h>

class OpenGL
{
public:
	OpenGL();

private:
	void Setup();
	void Update();
	void Render();
	void CleanUp();

	// Create an GLFW controlled context window
	GLFWwindow* Window;

	// Shader Program Reference
	GLuint shaderProgram;

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAOID;
	GLuint VBOID;
	GLuint EBOID;
	GLuint uniID;

	float CurrentTime;
	float Sinus;

};