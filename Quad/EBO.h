#pragma once
#include "OpenGLObject.h"
class EBO : public OpenGLObject
{
public:
	EBO(GLuint _ID, GLuint* _indices, GLsizeiptr _size);

	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void Delete() override;
};