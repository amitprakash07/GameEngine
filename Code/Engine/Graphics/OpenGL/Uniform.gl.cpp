#include "../Uniform.h"
#include "../../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../../Windows/WindowsFunctions.h"

Engine::Graphics::UniformData::UniformData()
{
	uniformName = nullptr;
	handle = -1;
	valType = NotKnown;
	valCount = 0xFF;
	shaderType = Unknown;
}


//void glUniform1f(GLint location,
//	GLfloat v0);
//
//void glUniform2f(GLint location,
//	GLfloat v0,
//	GLfloat v1);
//
//void glUniform3f(GLint location,
//	GLfloat v0,
//	GLfloat v1,
//	GLfloat v2);
//
//void glUniform4f(GLint location,
//	GLfloat v0,
//	GLfloat v1,
//	GLfloat v2,
//	GLfloat v3);
//
//void glUniform1i(GLint location,
//	GLint v0);
//
//void glUniform2i(GLint location,
//	GLint v0,
//	GLint v1);
//
//void glUniform3i(GLint location,
//	GLint v0,
//	GLint v1,
//	GLint v2);
//
//void glUniform4i(GLint location,
//	GLint v0,
//	GLint v1,
//	GLint v2,
//	GLint v3);
//
//void glUniform1ui(GLint location,
//	GLuint v0);
//
//void glUniform2ui(GLint location,
//	GLuint v0,
//	GLuint v1);
//
//void glUniform3ui(GLint location,
//	GLuint v0,
//	GLuint v1,
//	GLuint v2);
//
//void glUniform4ui(GLint location,
//	GLuint v0,
//	GLuint v1,
//	GLuint v2,
//	GLuint v3);
//
//void glUniform1fv(GLint location,
//	GLsizei count,
//	const GLfloat *value);
//
//void glUniform2fv(GLint location,
//	GLsizei count,
//	const GLfloat *value);
//
//void glUniform3fv(GLint location,
//	GLsizei count,
//	const GLfloat *value);
//
//void glUniform4fv(GLint location,
//	GLsizei count,
//	const GLfloat *value);
//
//void glUniform1iv(GLint location,
//	GLsizei count,
//	const GLint *value);
//
//void glUniform2iv(GLint location,
//	GLsizei count,
//	const GLint *value);
//
//void glUniform3iv(GLint location,
//	GLsizei count,
//	const GLint *value);
//
//void glUniform4iv(GLint location,
//	GLsizei count,
//	const GLint *value);
//
//void glUniform1uiv(GLint location,
//	GLsizei count,
//	const GLuint *value);
//
//void glUniform2uiv(GLint location,
//	GLsizei count,
//	const GLuint *value);
//
//void glUniform3uiv(GLint location,
//	GLsizei count,
//	const GLuint *value);
//
//void glUniform4uiv(GLint location,
//	GLsizei count,
//	const GLuint *value);
//
//void glUniformMatrix2fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix3fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix4fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix2x3fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix3x2fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix2x4fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix4x2fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix3x4fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);
//
//void glUniformMatrix4x3fv(GLint location,
//	GLsizei count,
//	GLboolean transpose,
//	const GLfloat *value);


void Engine::Graphics::Uniform::setValueInShaderObject() const
{
	switch (mUniform.valType)
	{
	case Bool:
		glUniform1ui(mUniform.handle,
			mUniform.value.boolValue);
		break;
	case BoolArray:
		glUniform1uiv(mUniform.handle,
			mUniform.valCount,
			reinterpret_cast<unsigned int *>(mUniform.value.boolArray));
		break;
	case Int:
		glUniform1i(mUniform.handle,
			mUniform.value.intValue);
	case IntArray:
		glUniform1iv(mUniform.handle,
			mUniform.valCount,
			reinterpret_cast<int *>(mUniform.value.intArray));
		break;
	case Float:
		glUniform1f(mUniform.handle,
			mUniform.value.floatValue);
		break;
	case FloatArray:
		glUniform1fv(mUniform.handle,
			mUniform.valCount,
			reinterpret_cast<float*>(mUniform.value.floatArray));
		break;
	case Matrix:
		glUniformMatrix4fv(mUniform.handle,
			mUniform.valCount,
			GL_FALSE,
			reinterpret_cast<const float*>(&mUniform.value.matrixValue.matrix));
		break;
	case MatrixArray:
		/*glUniformMatrix4fv(mUniform.handle,
		mUniform.valCount,
		GL_FALSE,
		reinterpret_cast<const float*>(mUniform.value.matrixArray->matrix));*/
		break;
	case Vector:
		glUniform4fv(mUniform.handle, 1,
			reinterpret_cast<const float*>(&mUniform.value.vectorValue));
		break;
	case VectorArray:
		glUniform4fv(mUniform.handle, mUniform.valCount,
			reinterpret_cast<const float*>(mUniform.value.vectorArray));
		break;
	default:
		break;
	}
	WindowsUtil::Assert(glGetError() == GL_NO_ERROR, "Unable to set the value");
}



