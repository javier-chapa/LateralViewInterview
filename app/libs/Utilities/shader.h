#pragma once

#include <GLES3/gl3.h>
#include <string>

using namespace std;

class Shader
{
public:
	GLuint program;
	Shader(string, string);
	void bind();
	void unbind();
	void errorLogHandler(GLuint, GLint, GLchar *);
	GLboolean validateShaderCompilation(GLuint, GLchar *);
	void uniform1f(GLchar *, GLfloat );
	void uniform2f(GLchar *, GLfloat , GLfloat );
	void uniform3f(GLchar *, GLfloat , GLfloat , GLfloat );
	void uniform4f(GLchar *, GLfloat , GLfloat , GLfloat , GLfloat );
	void uniform1i(GLchar *, GLint );
	void uniform2i(GLchar *, GLint , GLint );
	void uniform3i(GLchar *, GLint , GLint , GLint );
	void uniform4i(GLchar *, GLint , GLint , GLint , GLint );
	/*void uniform1ui(GLchar *, GLuint );
	void uniform2ui(GLchar *, GLuint , GLuint );
	void uniform3ui(GLchar *, GLuint , GLuint , GLuint );
	void uniform4ui(GLchar *, GLuint , GLuint , GLuint , GLuint );
	void uniform1fv(GLchar *, GLuint count, GLfloat *v);
	void uniform2fv(GLchar *, GLuint count, GLfloat *v);
	void uniform3fv(GLchar *, GLuint count, GLfloat *v);
	void uniform4fv(GLchar *, GLuint count, GLfloat *v);
	void uniform1iv(GLchar *, GLuint count, GLint *v);
	void uniform2iv(GLchar *, GLuint count, GLint *v);
	void uniform3iv(GLchar *, GLuint count, GLint *v);
	void uniform4iv(GLchar *, GLuint count, GLint *v);
	void uniform1uiv(GLchar *, GLuint count, GLuint *v);
	void uniform2uiv(GLchar *, GLuint count, GLuint *v);
	void uniform3uiv(GLchar *, GLuint count, GLuint *v);
	void uniform4uiv(GLchar *, GLuint count, GLuint *v);
	void uniformMatrix2fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix3fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix4fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix2x3fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix3x2fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix2x4fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix4x2fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix3x4fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);
	void uniformMatrix4x3fv(GLchar *, GLuint count, GLboolean transpose, GLfloat *v);*/
};