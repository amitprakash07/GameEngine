#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <string>
#include "../Engine/Core/Utilities/Sort.h"
#include "../Externals/OpenGLExtensions/OpenGlExtensions.h"
#include "../Engine/Core/Maths/Vector2.h"
#include "../Engine/Core/Maths/Matrix4x4.h"
#include <map>


#define MYSIZEOF(type) (char*)(&type+1)-(char*)(&type)
char* itoa(int value, int Base);

void BuildStringFromMatrix(int* Matrix,
	int NumRows, int NumCoulumns,
	char* OutBuffer);

int main()
{

	Engine::Math::Matrix4x4 tempMatrix =
		Engine::Math::Matrix4x4::CreateOrthographicViewToScreenTransform(
			0, 800, 0, 600, 0.1, 1000);

	Engine::Math::Vector3 tempVector =
		Engine::Math::Vector3(-98.0f, -101.0f, 1.0f);

	Engine::Math::Vector3 newVect =
		tempMatrix.mul(tempVector);






	//FT_Error error;
	//FT_Library ft;
	//if (FT_Init_FreeType(&ft))
	//{
	//	std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	//}

	//FT_Face face;
	//error = FT_New_Face(ft, "arial.ttf", 0, &face);

	//FT_Set_Pixel_Sizes(face, 0, 48);

	//if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	//	std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

	//struct Character {
	//	GLuint TextureID; // ID handle of the glyph texture
	//	Engine::Math::Vector2 Size; // Size of glyph
	//	Engine::Math::Vector2 Bearing; // Offset from baseline to left/top of glyph
	//	GLuint Advance; // Offset to advance to next glyph
	//};

	//std::map<GLchar, Character> Characters;

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	//for (GLubyte c = 0; c < 128; c++)
	//{
	//	// Load character glyph
	//	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	//	{
	//		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
	//		continue;
	//	}
	//	// Generate texture
	//	GLuint texture;
	//	glGenTextures(1, &texture);
	//	glBindTexture(GL_TEXTURE_2D, texture);
	//	glTexImage2D(
	//		GL_TEXTURE_2D,
	//		0,
	//		GL_RED,
	//		face->glyph->bitmap.width,
	//		face->glyph->bitmap.rows,
	//		0,
	//		GL_RED,
	//		GL_UNSIGNED_BYTE,
	//		face->glyph->bitmap.buffer
	//	);
	//	// Set texture options
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	// Now store character for later use
	//	Character character = {
	//		texture,
	//		Engine::Math::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
	//		Engine::Math::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
	//		face->glyph->advance.x
	//	};
	//	Characters.insert(std::pair<GLchar, Character>(c, character));
	//}

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//FT_Done_Face(face);
	//FT_Done_FreeType(ft);

	//Engine::Utils::Sort::TestMergeSort();
	/*unsigned int a = 0xFFFF;
	char * test = itoa(a & ((1<<10) - 1) , 2);
	std::cout << test << std::endl;
	std::string s;*/

	/*int b;

	std::cout << MYSIZEOF(b);
	std::cout << std::endl << &b;
	std::cout << std::endl << (&b) + 1;*/

	/*unsigned int a = 0x0000ffff;
	std::cout << itoa(a, 2);
	std::cout << std::endl<<itoa((a & 0xFFFF0000) >> 15 | (a & 0x0000FFFF) << 15, 2);*/

	////std::cout << (~a) + 1;
	/*int num = 100;
	int base = 8;
	char val[11];
	int i = 0;
	while(num !=0)
	{
		val[i++] = (num % base ) ==
	}*/

	/*unsigned int i = 0;
	int j = -1;
	bool test = j > (int)i;
	std::cout << test;*/

	//char a = '0' + 1;
	////std::cout << a;
	//char* some = new char[255];
	//int mat[] = { 1234,2,3,4,
	//			5,6,7,8,
	//			9,10,11,12};
	//BuildStringFromMatrix(mat, 4, 3, some);
	//std::cout <<std::endl<< some;
}


void BuildStringFromMatrix(int* Matrix,
	int NumRows, int NumColumn,
	char* OutBuffer)
{
	if (NumRows < 0 || NumColumn < 0)
	{
		OutBuffer = nullptr;
		return;
	}

	unsigned int stringIndex = 0;
	OutBuffer[stringIndex++] = '\"';

	int startRow = 0;
	int endRow = NumRows;
	int startColumn = 0;
	int endColumn = NumColumn;
	int *values = new int[NumRows*NumColumn];
	int valIndex = 0;

	while (startRow < endRow && startColumn < endColumn)
	{
		/* Evaluate the first row from the remaining rows */
		for (int i = startColumn; i < endColumn; ++i)
		{
			values[valIndex] = Matrix[startRow * NumColumn + i];
			valIndex++;
		}
		startRow++;

		/* Evaluate the last column from the remaining columns */
		for (int i = startRow; i < endRow; ++i)
		{
			values[valIndex] = Matrix[i * NumColumn + (endColumn - 1)];
			valIndex++;
		}
		endColumn--;

		/* Evaluate the last row from the remaining rows */
		if (startRow < endRow)
		{
			for (int i = endColumn - 1; i >= startColumn; --i)
			{
				values[valIndex] = Matrix[(endRow - 1)* NumColumn + i];
				valIndex++;				
			}
			endRow--;
		}

		/* Evaluate the first column from the remaining columns */
		if (startColumn < endColumn)
		{
			for (int i = endRow - 1; i >= startRow; --i)
			{
				values[valIndex] = Matrix[i * NumColumn + startColumn];
				valIndex++;				
			}
			startColumn++;
		}		
	}

	for (int i = 0; i < NumRows*NumColumn; i++)
	{
		int digitCount = 0;	
		char tempChar[32];
		int digitIndex = 31;
		while(values[i]!=0)
		{
			tempChar[digitIndex--] = 48 + static_cast<unsigned int>(values[i] % 10);
			values[i] = values[i] / 10;
			digitCount++;
		}
		
		digitIndex++;
		for(int j=0; j < digitCount; j++)
		{
			OutBuffer[stringIndex++] = tempChar[digitIndex++];
		}

		OutBuffer[stringIndex++] = ',';
		OutBuffer[stringIndex++] = ' ';
	}
	
	OutBuffer[stringIndex++] = '\b';
	OutBuffer[stringIndex++] = '\b';
	OutBuffer[stringIndex++] = '.';
	OutBuffer[stringIndex++] = '\"';
	OutBuffer[stringIndex] = '\0';
	delete values;
}



char* itoa(int value, int Base)
{
	char * itoaString = nullptr;
	char * digits = new char[Base];
	int length = 0;
	bool isValueNegative = false;
	//Checking if value is zero
	if(value ==0)
	{
		itoaString = new char[1];
		itoaString = "0\0";
		return itoaString;
	}

	//Checking if value is negative
	//if so making it positive
	if(value < 0)
	{
		value = -value;
		isValueNegative = true;
	}


	switch(Base)
	{
	case 8:
	{
		itoaString = new char[11];	
		char temp[] = "012345678\0";
		length = 11;
		memcpy(digits, temp, Base);
	}
		break;
	case 16:
	{
		itoaString = new char[8];		
		char temp[] = "0123456789ABCDEF\0";
		length = 8;
		memcpy(digits, temp, Base);
	}
		break;
	case 2:
	{
		itoaString = new char[32];
		length = 32;
		char temp[] = "01\0";		
		memcpy(digits, temp, Base);
	}
		break;
	}

	//For Positive Value
	if (!isValueNegative)
	{
		for (int i = 0; i < length; ++i)
			itoaString[i] = '0';

		int count = length;
		while (value != 0)
		{
			itoaString[--count] = digits[value % Base];
			value /= Base;
		}
	}
	//For negative Numbers
	else
	{
		char tempBinary[32];
		for (int i = 0; i < 32; ++i)
			tempBinary[i] = '1';
		
		int count = 31;
		int valBinaryLength = 0;
		//Coverting to Binary and taking 1's complement
		while (value != 0)
		{
			tempBinary[count] = digits[value % 2];
			if (tempBinary[count] == '0')
				tempBinary[count] = '1';
			else tempBinary[count] = '0';
			value /= 2;
			count--;			
			valBinaryLength++;
		}

		//Calculating 2's complement i.e negative representation
		bool carry = false;
		if (tempBinary[31] == '1')
		{
			carry = true;
			for (int i = 31; i >= valBinaryLength; i--)
			{
				if (tempBinary[i] == '1' && carry)
					tempBinary[i] = '0';
				else
				{
					tempBinary[i] = '1';
					carry = false;
					break;
				}
			}
		}
		else
			tempBinary[31] = '1';	


		switch(Base)
		{
		case 2:
			memcpy(itoaString, tempBinary, 32);
			break;
		case 8:
		{
			int octValCount = length - 1;;
			int octDigitVal = 0;;
			for (int i = 10; i > 0; i--)
				itoaString[i] = '7';
			itoaString[0] = '3';
			for (int i = 31; i >= 0; i = i - 3, octValCount--)
			{
				if (tempBinary[i] == '1')
					octDigitVal = 1;
				else
					octDigitVal = 0;

				if (tempBinary[i - 1] == '1')
					octDigitVal += 2;
				else
					octDigitVal += 0;

				if (tempBinary[i - 2] == '1')
					octDigitVal += 4;
				else
					octDigitVal += 0;

				itoaString[octValCount] = digits[octDigitVal];
				octDigitVal = 0;
			}
		}
			break;
		case 16:
		{
			int hexValCount = length - 1;
			int hexDigitVal = 0;
			for (int i = 10; i > 0; i--)
				itoaString[i] = 'F';

			for (int i = 31; i >= 0; i = i - 4, hexValCount--)
			{
				if (tempBinary[i] == '1')
					hexDigitVal = 1;
				else
					hexDigitVal = 0;

				if (tempBinary[i - 1] == '1')
					hexDigitVal += 2;
				else
					hexDigitVal += 0;

				if (tempBinary[i - 2] == '1')
					hexDigitVal += 4;
				else
					hexDigitVal += 0;

				if (tempBinary[i - 3] == '1')
					hexDigitVal += 8;
				else
					hexDigitVal += 0;

				itoaString[hexValCount] = digits[hexDigitVal];
				hexDigitVal = 0;
			}
		}
			break;
		}
	}

	itoaString[length] = '\0';	
	delete digits;
	return itoaString;
}


class X
{
	int * mMember;
};

void f()
{
	X a;
	X b(a);

}
class SingletonClass
{
public: 
	static void createSingleTonClass();
private:
	SingletonClass();
};
