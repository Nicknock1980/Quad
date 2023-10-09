#include "VBO.h"

VBO::VBO(GLuint _ID, GLfloat* _vertices, GLsizeiptr _size)
{
	ID = _ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}