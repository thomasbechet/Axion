#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>

#include <map>

namespace ax
{
	using ID = unsigned int;

	class AXION_CORE_API Observable;

	class AXION_CORE_API IObserver
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
		inline Observer() = default;
		inline Observer(T* observable)
		{
			this->operator=(observable);
		}
		inline ~Observer()
		{
			reset();
		}

		inline Observer<T>& operator=(T* observable)
		{
			if(observable != nullptr)
			{
				m_id = observable->addObserver(*this);
				m_ptr = observable;
			}
			else
			{
				reset();
			}

			return *this;
		}
		inline Observer<T>& operator=(Observer<T>& observer)
		{
			if(observer.isValid())
			{
				m_id = observer.get().addObserver(*this);
				m_ptr = &observer.get();
			}
			
			return *this;
		}
		inline T* operator->()
		{
			return m_ptr;	
		}

		inline T& get() const
		{
			return *m_ptr;
		}

		inline void reset() override
		{
			if(isValid())
			{
				m_ptr->removeObserver(m_id);
				m_ptr = nullptr;
			}
		}

		inline size_t observerCount() const noexcept
		{
			if(isValid())
			{
				return get().observerCount();
			}
			else return 0;
		}

		inline bool isValid() const noexcept
		{
			if(m_ptr == nullptr) return false;
			else return true;
		}

	private:
		T* m_ptr = nullptr;
		ID m_id;
	};

	class AXION_CORE_API Observable
	{
	public:
		template<typename T> friend class Observer;

	public:
		inline ~Observable()
		{
			for(auto it : m_observers)
			{
				it.second->reset();
			}
		}

		inline size_t observerCount() const noexcept
		{
			return m_observers.size();
		}
	private:
		inline ID addObserver(IObserver& observer)
		{
			ID id = m_idCounter++;
			m_observers[id] = &observer;

			return id;
		}
		inline void removeObserver(ID id)
		{
			m_observers.erase(id);
		}

	private:
		std::map<ID, IObserver*> m_observers;
		ID m_idCounter = 0;
	};
}