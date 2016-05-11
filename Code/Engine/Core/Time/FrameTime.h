#ifndef __FRAME_TIME_H
#define __FRAME_TIME_H

#include <stdint.h>
#include <windows.h>
#include "../Utilities/RTTI.h"


namespace Engine
{
	namespace Time
	{
		class FrameTime :public RTTI
		{
		public:

			static SharedPointer<FrameTime>		getFrameTimeController();
			void								pauseTimer(bool);
			bool								getTimerStatus();
			float								getdeltaTime();
			float								getdeltaTimeDuringFrame();
			void								updateDeltaTime();
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const  override { return true; }
			static uint64_t						getCurrentTick();

		private:
			uint64_t							lastTick;
			uint64_t							currentTick;
			uint64_t							pauseTimerTick;
			float								deltaTime;
			bool								isTimerPaused;
			uint64_t							frameTimeFrequency;
			FrameTime(LARGE_INTEGER *, LARGE_INTEGER *);
		};//FrameTime
	}//namespace Timing
}//namespace Engine

#endif