#include "UniquePtr.h"
#include <assert.h>

namespace Engine
{
	template<typename T>
	UniquePtr<T>::UniquePtr()
	{
		m_WrappingObject = new T;
	}

	template<typename T>
	bool UniquePtr<T>::deleteObject()
	{
		assert(m_WrappingObject);
		delete m_WrappingObject;
		if (m_WrappingObject == nullptr)
			return true;
		return false;
	}

	template<typename T>
	UniquePtr<T>::~UniquePtr()
	{
		deleteObject();
	}

	template<typename T>
	UniquePtr<T>::UniquePtr(UniquePtr<T> &i_ptr)
	{
		m_WrappingObject = i_ptr.m_WrappingObject;
		i_ptr.deleteObject();
	}

	template<typename T>
	UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr& i_other)
	{
		if (m_WrappingObject != nullptr)
		{
			deleteObject(this);
			m_WrappingObject = i_other.m_WrappingObject;
			return *this;
		}
	}

	template<typename T>
	T& UniquePtr<T>:: operator*()
	{
		assert(m_WrappingObject);
		return *(m_WrappingObject);
	}

	template<typename T>
	T* UniquePtr<T>::operator->()
	{
		assert(m_WrappingObject);
		return m_WrappingObject;
	}
}//namespace Engine