#ifndef __SHARED_PTR_H
#define __SHARED_PTR_H

#include "RTTI.h"

namespace Engine
{
	template<typename T>
	class SharedPointer
	{
	public:
		SharedPointer();
		SharedPointer(T *, std::string);
		bool deleteObject();
		SharedPointer(const SharedPointer<T> &);
		SharedPointer<T>& operator=(SharedPointer<T> &);
		//bool isBothSameType(RTTI* i_ptr);
		bool isEqual(const SharedPointer<T> &) const;
		//SharedPointer(SharedPointer<T> *);
		T& operator*();
		T* operator->() const;
		~SharedPointer();
		bool isNull() const;
		RTTI* getRawPointer() const;

	private:
		T*				m_WrappingObject;
		unsigned int	*m_referenceCount;
		std::string     m_typeName;
	}; //SharedPointer
}//Engine

#include "SharedPointer.inl"


 //template <>
 //inline bool Engine::SharedPointer<Engine::RTTI>::isBothSameType(Engine::RTTI* i_ptr)
 //{
 //	if (i_ptr)
 //	{
 //		if (m_WrappingObject->isType(i_ptr))
 //			return true;
 //		return false;
 //	}
 //	return false;
 //}


#endif //SHARED_PTR_H