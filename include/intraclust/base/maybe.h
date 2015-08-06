#ifndef INTRACLUST_MAYBE
#define INTRACLUST_MAYBE

#include <allocators>
#include <future>
#include <mutex>
#include <exception>

namespace intraclust
{
	namespace base
	{

		template<typename Type>
		class Maybe
		{
		public:

			using error_type = std::exception;
			using value_type = Type;

		public:
			Maybe(value_type data)
				: data(std::forward<value_type>(data))
				, error(nullptr)
			{}

			Maybe()
				: data(nullptr)
				, error(nullptr)
			{}


			Maybe(decltype(nullptr) nothing)
				: data(nullptr)
				, error(nullptr)
			{}

			Maybe(error_type&& error)
				: data(nullptr)
				, error(std::make_shared<error_type>(error))
			{}

			bool isEmpty()
			{
				return (data == nullptr);
			}

			bool hasError()
			{
				return (error != nullptr);
			}

			value_type operator()()
			{
				return data;
			}

			std::shared_ptr<error_type> getError()
			{
				return error;
			};


			explicit operator bool() const _NOEXCEPT
			{
				return (error == nullptr);
			}

		private:
			const value_type data;
			const std::shared_ptr<error_type> error;
		};




		template <class T>
		Maybe<T> just(T t)
		{
			return Maybe<T>(t);
		}

	} // ns base
} // ns intraclust

#endif /* INTRACLUST_MAYBE */
