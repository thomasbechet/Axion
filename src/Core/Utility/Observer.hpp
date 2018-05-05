#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>

#include <map>

namespace ax
{
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
		using Id = unsigned;

	public:
		Observer() = default;
		Observer(T* observable)
		{
			this->operator=(observable);
		}
		~Observer()
		{
			reset();
		}

		Observer<T>& operator=(T* observable)
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
		Observer<T>& operator=(Observer<T>& observer)
		{
			if(observer.isValid())
			{
				m_id = observer.get().addObserver(*this);
				m_ptr = &observer.get();
			}
			
			return *this;
		}
		T* operator->()
		{
			return m_ptr;	
		}

		T& get() const noexcept
		{
			return *m_ptr;
		}

		void reset() override
		{
			if(isValid())
			{
				m_ptr->removeObserver(m_id);
				m_ptr = nullptr;
			}
		}

		size_t observerCount() const noexcept
		{
			if(isValid())
			{
				return get().observerCount();
			}
			else return 0;
		}

		bool isValid() const noexcept
		{
			if(m_ptr == nullptr) return false;
			else return true;
		}

	private:
		T* m_ptr = nullptr;
		Id m_id;
	};

	class AXION_CORE_API Observable
	{
	public:
		template<typename T> friend class Observer;

	public:
		~Observable()
		{
			for(auto it : m_observers)
			{
				it.second->reset();
			}
		}

		size_t observerCount() const noexcept
		{
			return m_observers.size();
		}
	private:
		Id addObserver(IObserver& observer) noexcept
		{
			Id id = m_idCounter++;
			m_observers[id] = &observer;

			return id;
		}
		void removeObserver(Id id) noexcept
		{
			m_observers.erase(id);
		}

	private:
		std::map<Id, IObserver*> m_observers;
		Id m_idCounter = 0;
	};
}