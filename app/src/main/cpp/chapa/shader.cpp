#include <Utilities/shader.h>
#include <Utilities/utilities.h>
#include <GLES3/gl3.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

Shader::Shader(string vert, string frag)
{
	const GLubyte *version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
	char *vs = readAsset(vert);
	char *fs = readAsset(frag);
	const GLchar *vv = vs;
	const GLchar *ff = fs;
	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
	delete [] vs;
	delete [] fs;
	glCompileShader(v);
	validateShaderCompilation(v, "vertex.txt");
	glCompileShader(f);
	validateShaderCompilation(f, "fragment.txt");
	program = glCreateProgram();
	glAttachShader(this->program,v);
	glAttachShader(this->program,f);
	glLinkProgram(this->program);
}

void Shader::bind()
{
	glUseProgram(this->program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::errorLogHandler(GLuint object, GLint len, GLchar *file)
{
	GLsizei slen = 0;
	std::ofstream log(file,std::ios::out);
	GLchar *errlog = new GLchar[len];
	glGetShaderInfoLog(object,len, &slen, errlog);
	log << errlog;
	delete [] errlog;
}

GLboolean Shader::validateShaderCompilation(GLuint shader, GLchar *log)
{
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint GLintfoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &GLintfoLen);
        if (GLintfoLen)
        {
            GLchar * buf = (GLchar*) malloc(GLintfoLen);
            if (buf)
            {
                glGetShaderInfoLog(shader, GLintfoLen, NULL, buf);
                free(buf);
            }
            glDeleteShader(shader);
            shader = 0;
        }
        return GL_FALSE;
    }
    return GL_TRUE;
}

void Shader::uniform1f(GLchar *location, GLfloat v0)
{
	glUniform1f(glGetUniformLocation(this->program, location), v0);
}

void Shader::uniform2f(GLchar *location, GLfloat v0, GLfloat v1)
{
	glUniform2f(glGetUniformLocation(this->program, location), v0, v1);
}

void Shader::uniform3f(GLchar *location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(glGetUniformLocation(this->program, location), v0, v1, v2);
}

void Shader::uniform4f(GLchar *location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(glGetUniformLocation(this->program, location), v0, v1, v2, v3);
}

void Shader::uniform1i(GLchar *location, GLint v0)
{
	glUniform1i(glGetUniformLocation(this->program, location), v0);
}

void Shader::uniform2i(GLchar *location, GLint v0, GLint v1)
{
	glUniform2i(glGetUniformLocation(this->program, location), v0, v1);
}

void Shader::uniform3i(GLchar *location, GLint v0, GLint v1, GLint v2)
{
	glUniform3i(glGetUniformLocation(this->program, location), v0, v1, v2);
}

void Shader::uniform4i(GLchar *location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	glUniform4i(glGetUniformLocation(this->program, location), v0, v1, v2, v3);
}
/*
void Shader::uniform1ui(GLchar *location, GLuint v0)
{
	glUniform1ui(glGetUniformLocation(this->program, location), v0);
}

void Shader::uniform2ui(GLchar *location, GLuint v0, GLuint v1)
{
	glUniform2ui(glGetUniformLocation(this->program, location), v0, v1);
}

void Shader::uniform3ui(GLchar *location, GLuint v0, GLuint v1, GLuint v2)
{
	glUniform3ui(glGetUniformLocation(this->program, location), v0, v1, v2);
}

void Shader::uniform4ui(GLchar *location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glUniform4ui(glGetUniformLocation(this->program, location), v0, v1, v2, v3);
}

void Shader::uniform1fv(GLchar *location, GLuint count, GLfloat *v)
{
	glUniform1fv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform2fv(GLchar *location, GLuint count, GLfloat *v)
{
	glUniform2fv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform3fv(GLchar *location, GLuint count, GLfloat *v)
{
	glUniform3fv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform4fv(GLchar *location, GLuint count, GLfloat *v)
{
	glUniform4fv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform1iv(GLchar *location, GLuint count, GLint *v)
{
	glUniform1iv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform2iv(GLchar *location, GLuint count, GLint *v)
{
	glUniform2iv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform3iv(GLchar *location, GLuint count, GLint *v)
{
	glUniform3iv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform4iv(GLchar *location, GLuint count, GLint *v)
{
	glUniform4iv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform1uiv(GLchar *location, GLuint count, GLuint *v)
{
	glUniform1uiv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform2uiv(GLchar *location, GLuint count, GLuint *v)
{
	glUniform2uiv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform3uiv(GLchar *location, GLuint count, GLuint *v)
{
	glUniform3uiv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniform4uiv(GLchar *location, GLuint count, GLuint *v)
{
	glUniform4uiv(glGetUniformLocation(this->program, location), count, v);
}

void Shader::uniformMatrix2fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix2fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix3fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix3fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix4fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix2x3fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix2x3fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix3x2fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix3x2fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix2x4fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix2x4fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix4x2fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix4x2fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix3x4fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix3x4fv(glGetUniformLocation(this->program, location), count, transpose, v);
}

void Shader::uniformMatrix4x3fv(GLchar *location, GLuint count, GLboolean transpose, GLfloat *v)
{
	glUniformMatrix4x3fv(glGetUniformLocation(this->program, location), count, transpose, v);
}
 */