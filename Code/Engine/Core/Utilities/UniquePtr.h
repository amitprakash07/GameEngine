#ifndef __UNIQUE_PTR
#define __UNIQUE_PTR


namespace Engine
{
	template<typename T>
	class UniquePtr
	{
	public:
		UniquePtr();
		bool deleteObject();
		~UniquePtr();
		UniquePtr(UniquePtr &);
		UniquePtr& operator=(UniquePtr &);
		T& operator*();
		T* operator->();
	private:

		T* m_WrappingObject;
	}; //UniquePtr
}// namespace Engine
#endif //header guard