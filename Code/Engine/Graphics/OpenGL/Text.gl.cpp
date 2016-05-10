#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Text.h"
#include <iostream>
#include "../../Windows/WindowsFunctions.h"
#include "../Effect.h"
#include "../../Core/EngineCore/EngineCore.h"
#include "../../Core/EngineCore/Objects/Scene.h"
#include "../../../Engine/Core/Maths/Functions.h"

bool Engine::Graphics::Text::InitializeTexturesForCharacters(std::string iFont)
{
	FT_Error error;
	FT_Library ft;
	error = FT_Init_FreeType(&ft);
	
	WindowsUtil::Assert(error == 0, "Unable to Load the FreeType Library");		
	FT_Face face;
	error = FT_New_Face(ft, iFont.c_str(), 0, &face);
	WindowsUtil::Assert(error == 0, "Unable to Load the FreeType Face");	

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	std::map<GLchar, Character> tempCharacter;

	for (GLubyte c = 0; c < 255; c++)
	{
		// Load character glyph 
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		WindowsUtil::Assert(error == 0, "ERROR::FREETYTPE: Failed to load Glyph");
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			Math::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			Math::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			Math::Vector2(face->glyph->advance.x, face->glyph->advance.y)			
		};
		tempCharacter[c] = character;
	}
	
	Characters[iFont] = tempCharacter;
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	return true;
}


void Engine::Graphics::Text::InitializeText()
{
	GLenum errorCode;
	glGenVertexArrays(1, &vertexArray);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do generate vertexArray");

	glBindVertexArray(vertexArray);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do Bind VertexArray");

	glGenBuffers(1, &vertexBuffer);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do generate vertexBuffer");	

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do bind vertexBuffer");

	glVertexAttribPointer(0,
		4,
		GL_FLOAT, GL_FALSE,
		0, nullptr);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do define vertex Attribute Pointer");

	glEnableVertexAttribArray(0);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do enable vertexAttribute Pointer");

	Effect::addEffectToList(mEffectFileName);
	GLuint programID = Effect::getEffect(mEffectFileName)->GetProgramID();
	
	textColor =
		glGetUniformLocation(programID, "textColor");
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do get the uniform Location");
}


void Engine::Graphics::Text::draw(bool drawDebugObject)
{
	GLenum errorCode;
	Effect::getEffect(mEffectFileName)->setShaders();
	int width = Engine::EngineCore::getWindowingSystem()->getWindowWidth();
	int height = Engine::EngineCore::getWindowingSystem()->getWindowHeight();
	
	float sx = mScale.x / width;
	float sy = mScale.x / height;

	glUniform4fv(textColor, 1,
		reinterpret_cast<float*>(&mColor));
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do pass matrix data");

	glBindVertexArray(vertexArray);
	errorCode = glGetError();
	WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do bind vertexArray");

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	
	float x = Math::scaleAndBias(mTransform.getPosition().x, 0, width, -1,1);
	float y = Math::scaleAndBias(mTransform.getPosition().y,0, height, -1,1);

	for (std::string::iterator c = textToBeRendered.begin();
		c!=textToBeRendered.end(); ++c)
	{
		Character ch = Characters[mFontName][*c];
		
		/*GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;*/

		float x2 = x + ch.Bearing.x * sx;
		float y2 = -y - ch.Bearing.y * sy;
		float w = ch.Size.x * sx;
		float h = ch.Size.y * sy;

		// Update VBO for each character
		/*GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};*/

		GLfloat box[4][4] = {
			{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do bind texture");

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to bind vertex buffer");

		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW); // Be sure to use glBufferSubData and not glBufferData
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do push vertex data");

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		errorCode = glGetError();
		WindowsUtil::Assert(errorCode == GL_NO_ERROR, "Unable to do draw quad");
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance.x/ 64) * sx;
		y += (ch.Advance.y / 64) * sy;
	}
}
