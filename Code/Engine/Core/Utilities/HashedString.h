#ifndef __HASHED_STRING_H
#define __HASHED_STRING_H

#include "RTTI.h"

namespace Engine
{
	namespace utils
	{
		class StringHash :public RTTI
		{
		public:
			StringHash();
			StringHash(const char*);
			StringHash(const StringHash &);

			unsigned __int32						getHash() const;
			StringHash &							operator=(const StringHash &);
			bool									operator !=(const StringHash&) const;
			bool									operator==(const StringHash &) const;
			bool									operator < (const StringHash &) const;
			static unsigned __int32					Hash(const char *);
			static unsigned __int32					Hash(const void *, size_t);
			bool									isNil() const;
			std::string getTypeInfo() const override { return ""; }
			bool isBothSameType(SharedPointer<RTTI>, std::string) const override { return true; }

		private:
			unsigned __int32 mHash;
#ifdef _DEBUG
			char *mString;
#endif
		};
	}//namespace utils
}//namespace myEngine

#endif //__HASHED_STRING_H