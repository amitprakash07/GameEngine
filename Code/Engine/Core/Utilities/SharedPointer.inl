#include <assert.h>


namespace Engine
{
	template <typename T>
	inline SharedPointer<T>::SharedPointer()
	{
		m_WrappingObject = nullptr;
		m_referenceCount = new unsigned int;
		*m_referenceCount = 0;
		m_typeName = "";
	}

	template<typename T>
	inline SharedPointer<T>::SharedPointer(T* i_ptr, std::string i_typeName)
	{
		assert(i_ptr != nullptr);
		m_WrappingObject = i_ptr;
		m_referenceCount = new unsigned int;
		*m_referenceCount = 1;
		m_typeName = i_typeName;
	}

	template<typename T>
	inline SharedPointer<T>::~SharedPointer()
	{
		deleteObject();
	}

	template<typename T>
	inline SharedPointer<T>::SharedPointer(const SharedPointer<T> & i_other)
	{
		m_WrappingObject = i_other.m_WrappingObject;
		m_referenceCount = i_other.m_referenceCount;
		(*(m_referenceCount))++;
		m_typeName = i_other.m_typeName;
	}

	/*template<typename T>
	inline SharedPointer<T>::SharedPointer(SharedPointer<T> * i_other)
	{
	m_WrappingObject = i_other.m_WrappingObject;
	m_referenceCount = i_other.m_referenceCount;
	(*(m_referenceCount))++;
	}*/

	template<typename T>
	inline SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T> &i_other)
	{
		if (!isEqual(i_other))
		{
			if (!isNull()) deleteObject();
			m_WrappingObject = i_other.m_WrappingObject;
			assert(i_other.m_referenceCount);
			m_referenceCount = i_other.m_referenceCount;
			(*(m_referenceCount))++;
			m_typeName = i_other.m_typeName;
		}
		return *(this);
	}

	template<typename T>
	inline bool SharedPointer<T>::isEqual(const SharedPointer<T> &i_other) const
	{
		if (m_WrappingObject == i_other.m_WrappingObject)
			return true;
		return false;
	}


	template<typename T>
	inline T& SharedPointer<T>::operator*()
	{
		assert(m_WrappingObject);
		return *m_WrappingObject;
	}

	template<typename T>
	inline T* SharedPointer<T>::operator->() const
	{
		assert(m_WrappingObject);
		if (!this->isNull())
			return m_WrappingObject;
		return nullptr;
	}

	template<typename T>
	inline bool SharedPointer<T>::deleteObject()
	{
		assert(m_WrappingObject);
		if (!this->isNull())
		{
			if ((*m_referenceCount - 1) == 0)
			{
				//EngineController::GameEngine::isEngineInitialized() ? EngineController::GameEngine::getMemoryManager()->__free(m_WrappingObject) : delete m_WrappingObject; 
				if (m_WrappingObject)
					delete m_WrappingObject;
				if (m_referenceCount)
					delete m_referenceCount;
				m_WrappingObject = nullptr;
			}
			else
				(*m_referenceCount)--;

			return true;
		}
		return false;
	}

	template<typename T>
	inline bool SharedPointer<T>::isNull() const
	{
		if (m_WrappingObject == nullptr)//|| m_WrappingObject == null)
			return true;
		else return false;
	}

	template<typename T>
	inline Engine::RTTI* SharedPointer<T>::getRawPointer()
	{
		return(reinterpret_cast<RTTI*>(m_WrappingObject));
	}

} //Engine