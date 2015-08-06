#ifndef INTRACLUST_CONTAINER_ALGORITHM
#define INTRACLUST_CONTAINER_ALGORITHM

#include <allocators>
#include <future>
#include <mutex>
#include <exception>

namespace intraclust
{
	namespace base
	{
		namespace container
		{

			template<class _InIt,
			class _Pr> inline
				bool contains(_InIt _First, _InIt _Last, _Pr _Pred)
			{
				return std::find_if(_First, _Last, _Pred) != _Last;
			}

			template<class _InIt,
			class _Pr> inline
				bool contains_not(_InIt _First, _InIt _Last, _Pr _Pred)
			{
				return std::find_if(_First, _Last, _Pred) == _Last;
			}

			template<class _InIt, class T, class _Pr> 
			inline bool find_by_compare(_InIt _First, _InIt _Last, , const T& val, _Pr _Pred)
			{
				auto it = _First;
				for (; it != _Last; ++it)
				{
					if (_Pred(*it, val))
						return true;
				}

				return false;
			}


			template<class ItemType, class _inIt, class _Pr>
			typename std::vector<ItemType> searchAll(_inIt _First, _inIt _Last, _Pr _Pred)
			{
				_inIt there;

				typename std::vector<ItemType> c;

				do {
					there = std::search(_first, _Last, _Pred);

					c.insert(there, *there);

				} while (there != _Last);
			}




		} // ns container
	} // ns base
} // ns intraclust

#endif /* INTRACLUST_CONTAINER_ALGORITHM */
