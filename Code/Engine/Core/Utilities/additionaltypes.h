#ifndef __ADD_TYPES_H
#define __ADD_TYPES_H

#include <cstdint>
#include <cstring>

namespace Engine
{
	namespace typedefs
	{
		enum Priority:uint8_t
		{
			HIGH = 0,
			MODERATE = 1,
			LOW = 2
		};		

		enum Action :uint8_t
		{
			Zoom = 0,
			ArcBallRotate = 1,
			Rotate = 2,
			Pan = 3,
			MoveForward = 4,
			MoveBackWard = 5,
			MoveLeft = 6,
			MoveRight = 7,
			Jump = 8,
			Duck = 9,
			Attack = 10,
			RotateLeft = 11,
			RotateRight = 12,
			RotateUp = 13,
			RotateDown = 14,
			Default = 15
		};	

		struct ActionWithKeyBound
		{
			Action action;
			uint64_t keyVal;
		};

		struct _String
		{
			char *mString;
			size_t mStringLength;

			_String()
			{
				mString = nullptr;
				mStringLength = 0;
			}

			_String(char * i_char)
			{
				mString = _strdup(i_char);
				mStringLength = strlen(mString);
			}

			char * getAsChar() const
			{
				return mString;
			}

			size_t getLength() const
			{
				return mStringLength;
			}
		};
		typedef _String String;
		
	}//namespace typedefs
}//namespace myEngine

#endif //__TYPES_H
