#ifndef __EFFECTS_H
#define __EFFECTS_H

#include "Effect.h"

namespace Engine
{
	namespace Graphics
	{
		class Effects
		{
		public:
			static bool addEffect(std::string, std::string);
			static void removeAllEffects();
			Effects();
			~Effects();
		private:
			static std::vector<Effect*> effects;			
		};
	}
}

#endif