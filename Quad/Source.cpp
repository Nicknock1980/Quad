#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void Setup();
void Update();
void Render();
void CleanUp();

// Create an GLFW controlled context window
GLFWwindow* Window = nullptr;

// Shader Program Reference
GLuint shaderProgram;

// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
GLuint VAOID, VBOID, EBOID;

// Gets ID of uniform called "scale"
GLuint uniID;

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main()
{
	// Setup the initial elements of the program
	Setup();

	// Main loop
	while (glfwWindowShouldClose(Window) == false)
	{
		// Updates all objects and run the processes
		Update();

		// Render all the objects
		Render();
	}

	// Cleaning up objects and windows
	CleanUp();
	return 0;
}

// Setup the initial elements of the program
void Setup()
{

	// Initializing GLFW and setting the version to 4.6 with only Core functionality available
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	Window = glfwCreateWindow(800, 800, "First OpenGL Window", NULL, NULL);
	if (Window == NULL)
	{
		std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
		system("pause");
		glfwTerminate();
		return;
	}glfwMakeContextCurrent(Window);

	// Initializing GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Maps the range of window size to ndc (-1 -> to 1)
	glViewport(0, 0, 800, 800);

	shaderProgram = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vs", "Resources/Shaders/FixedColor.fs");

	// Generate the VAO and VBO and EBO
	VAO vao = VAO(VAOID);
	VBO vbo = VBO(VBOID, vertices, sizeof(vertices));
	EBO ebo = EBO(EBOID, indices, sizeof(indices));

	// Make the VAO the current Vertex Array Object by binding it
	vao.Bind();

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	// Enable the Vertex Attribute so that OpenGL knows to use it
	vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.LinkVBO(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Bind EBO, VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	// Gets ID of uniform called "scale"
	uniID = glGetUniformLocation(shaderProgram, "scale");

}

// Renders all the objects
void Render()
{
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Tell OpenGL which Shader Program we want to use
	glUseProgram(shaderProgram);

	// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
	glUniform1f(uniID, 0.5f);

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAOID);

	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(Window);

}

// Update all objects and run the processes
void Update()
{
	// Take care of all GLFW events
	glfwPollEvents();
}

void CleanUp()
{
	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAOID);
	glDeleteBuffers(1, &VBOID);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(Window);

	// Terminate GLFW before ending the program
	glfwTerminate();
}