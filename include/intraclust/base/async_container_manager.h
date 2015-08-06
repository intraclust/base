#ifndef INTRACLUST_ASYNC_CONTAINER_MANAGER
#define INTRACLUST_ASYNC_CONTAINER_MANAGER

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

			template<template<typename, typename> ContainerType,
				typename Type,
				typename Allocator = std::allocator<Type> >
			class AsyncManager
			{
			public:
				using container_type = ContainerType<Type, Allocator>;
				using allocator_type = Allocator;
				using hold_type = Type;

			public:

				AsyncManager()
				{}

				AsyncManager(const Type& arg)
				{
					addItem(arg);
				}

				AsyncManager(Type... args)
				{
					addItem(std::forward<Type>(args)...);
				}

				std::future<Type> operator[](const int index)
				{
					std::unique_lock<std::mutex> m(mutex_);

					if (container_.size() >= index)
						return container_[index];

					throw std::out_of_range("Index is out of Range");
				}

				void addItem(const Type& item)
				{
					auto push = [item, this]()->Type{
						std::unique_lock<std::mutex> m(mutex_);
						container_.push_back(item);
					};

					std::async(push);

					
				}


				std::future<Type> removeItem(const Type& item)
				{
					auto func = [item, this]() throws(std::runtime_error) {
						std::unique_lock<std::mutex> m(mutex_);

						auto itr = std::find(container_.begin(), container_.end(), item);
						if (itr != container_.end())
							container_.erase(itr);
						else
							throw std::runtime_error("This item does not exist");
					};

					return std::async(func);
				}

			private:
				container_type container_;
				mutable std::mutex mutex_;
			};

		} // ns container
	} // ns base
} // ns intraclust

#endif /* INTRACLUST_ASYNC_CONTAINER_MANAGER */
