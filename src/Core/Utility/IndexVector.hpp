#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>

#include <vector>
#include <exception>
#include <utility>

namespace ax
{
	template<typename C>
	class AXION_CORE_API IndexVector
	{
	public:
		using iterator = typename std::vector<C>::iterator;

	public:
		Id add(C&& element)
		{
			if(m_free.empty())
			{
				m_list.push_back(std::forward<C>(element));
				m_index.push_back(m_list.size() - 1);
				m_backList.push_back(m_index.size() - 1);
				return m_index.back() + 1;
			}
			else
			{
				Id freeIndex = m_free.back();
				m_free.pop_back();
				
				m_list.push_back(std::forward<C>(element));
				m_backList.push_back(freeIndex);
				m_index[freeIndex] = m_list.size() - 1;

				return freeIndex + 1;
			}
		}
		Id add(C& element)
		{
			return add(std::move(element));
		}
		void remove(Id index)
		{
			index--;

			Id element = m_index[index];

			m_index[m_backList.back()] = element;
			m_list[element] = std::move(m_list.back());

			m_list.pop_back();
			m_backList.pop_back();

			m_free.push_back(index);
		}

		void clear()
		{
			m_list.clear();
			m_free.clear();
			m_index.clear();
		}

		C& get(Id index)
		{
			index--;
			return m_list[m_index[index]];
		}

		iterator begin()
		{
			return m_list.begin();
		}
		iterator end()
		{
			return m_list.end();
		}

		size_t size() const noexcept
		{
			return m_list.size();
		}
		size_t capacity() const noexcept
		{
			return m_list.capacity();
		}
		void reserve(size_t size)
		{
			m_list.reserve(size);
		}
		bool empty() const noexcept
		{
			return m_list.empty();
		}
		C* data() const noexcept
		{
			return m_list.data();
		}

	private:
		std::vector<C> m_list;
		std::vector<Id> m_backList;
		std::vector<Id> m_index;
		std::vector<Id> m_free;
	};
}

