#pragma once
#include "OpenGLObject.h"
class VBO : public OpenGLObject
{
public:
	VBO(GLuint _ID, GLfloat* _vertices, GLsizeiptr _size);

	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void Delete() override;
};

