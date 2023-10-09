#pragma once
#include "OpenGLObject.h"
class VAO : public OpenGLObject
{
public:
	VAO(GLuint _ID);

	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void Delete() override;

	void LinkVBO(class VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
};

