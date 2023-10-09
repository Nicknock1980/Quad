#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class OpenGLObject
{
public:
	OpenGLObject() { ID = 0; };

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Delete() = 0;

protected:
	GLuint ID;

};