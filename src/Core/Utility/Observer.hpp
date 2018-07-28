#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/NonCopyable.hpp>

#include <vector>

namespace ax
{
	class AXION_CORE_API Observable;

	class AXION_CORE_API IObserver : public NonCopyable
	{
	public:
		virtual void reset() = 0;
	};

	template<typename T>
	class AXION_CORE_API Observer : public IObserver
	{
	public:
		friend class Observable;

	public:
		Observer(T* observable) {operator=(observable);}
		~Observer() {reset();}

		Observer<T>& operator=(T* observable)
		{
			reset();

			if(observable != nullptr)
			{
				observable->addObserver(*this);
				m_ptr = observable;
			}

			return *this;
		}
		T* operator->() {return m_ptr;}
		T& operator*() {return *m_ptr;}
		T& get() const noexcept {return *m_ptr;}

		void reset() override
		{
			if(isValid()) m_ptr->removeObserver(m_id);
			m_ptr = nullptr;
		}

		size_t observerCount() const noexcept
		{
			if(isValid()) return get().observerCount();
			else return 0;
		}
		bool isValid() const noexcept
		{
			if(m_ptr == nullptr) return false;
			else return true;
		}

	private:
		T* m_ptr = nullptr;
	};

	class AXION_CORE_API Observable : public NonCopyable
	{
	public:
		template<typename T> friend class Observer;

	public:
		~Observable()
		{
			for(auto it : m_observers)
				it->reset();
		}

		size_t observerCount() const noexcept {return m_observers.size();}

	private:
		void addObserver(IObserver& observer) noexcept {return m_observers.emplace_back(observer);}
		void removeObserver(IObserver& observer) noexcept {m_observers.erase(observer);}

	private:
		std::vector<IObserver*> m_observers;
	};
}