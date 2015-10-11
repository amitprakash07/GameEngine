#ifndef __SHARED_PTR_H
#define __SHARED_PTR_H

namespace Engine
{
	template<typename T>
	class SharedPointer
	{
	public:
		SharedPointer();
		SharedPointer(T *);
		bool deleteObject();
		SharedPointer(const SharedPointer<T> &);
		SharedPointer<T>& operator=(SharedPointer<T> &);
		bool isEqual(SharedPointer<T> &);
		SharedPointer(SharedPointer<T> *);
		T& operator*();
		T* operator->();
		~SharedPointer();
		bool isNull();

	private:
		T*				m_WrappingObject;
		unsigned int	*m_referenceCount;
	}; //SharedPointer
}//Engine

#include "SharedPointer.inl"

#endif //SHARED_PTR_H