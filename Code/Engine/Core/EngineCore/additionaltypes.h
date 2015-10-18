#ifndef __ADD_TYPES_H
#define __ADD_TYPES_H

#include <string.h>
#include <limits.h>

namespace Engine
{
	namespace typedefs
	{
		enum _Alignment
		{
			ALIGNMENT_2 = 2,
			ALIGNMENT_4 = 4,
			ALIGNMENT_8 = 8,
			ALIGNMENT_16 = 16,
			ALIGNMENT_32 = 32,
			ALIGNMENT_64
		};
		typedef _Alignment Alignment;

		enum _MessagePriority
		{
			HIGH = 0,
			MODERATE = 1,
			LOW = 2
		};
		typedef _MessagePriority Priority;

		enum _Direction
		{
			NONE,
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		typedef _Direction Direction;

		enum _Axis
		{
			XAxis = 0,
			YAxis = 1,
			ZAxis = 2
		};
		typedef _Axis Axis;


		enum _LOG_LEVEL
		{
			NO_LOG = 0,
			DEBUG_LOG = 1,
			WARNING_LOG = 2,
			ERROR_LOG = 4,
			// Compare only, should not use
			DEBUG_WARNING_LOG = 3,
			DEBUG_ERROR_LOG = 5,
			WARNING_ERROR_LOG = 6,
			DEBUG_WARNING_ERROR_LOG = 7
		};
		typedef _LOG_LEVEL LOG_LEVEL;

		struct _String
		{
			char *mString;
			size_t mStringLength;// = strlen(mString);

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
			
			char * getAsChar()
			{
				return mString;
			}

			size_t getLength()
			{
				return mStringLength;
			}
		};
		typedef _String String;

		
		struct _Accumulator
		{
			unsigned int	m_Count;
			unsigned int	m_Sum;
			unsigned int	m_Max;
			unsigned int	m_Min;

			_Accumulator()
			{
				m_Count = 0;
				m_Sum = 0;
				m_Max = 0;
				m_Min = UINT_MAX;
			}
		};
		typedef _Accumulator Accumulator;


		/*struct _boundingbox
		{
			Vector3D position;
			float width;
			float height;
			float depth;
		};
		typedef _boundingbox BoundingBox;*/


		struct _screenResolution
		{
			int width;
			int height;

			_screenResolution()
			{
				width = 1024;
				height = 768;
			}

			_screenResolution(int i_width, int i_height)
			{
				width = i_width;
				height = i_height;
			}
		};
		typedef _screenResolution ScreenResolution;

		struct _RGBA
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
		typedef _RGBA RGBA;

		enum __MatrixMajor
		{
			COLUMN_MAJOR = 0,
			ROW_MAJOR = 1
		};
		typedef __MatrixMajor MatrixMajor;
	}//namespace typedefs
}//namespace myEngine

#endif //__TYPES_H
