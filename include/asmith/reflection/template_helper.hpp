//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#include <type_traits>
#include <cstdint>
#include <string>

#ifndef ASMITH_REFLECTION_TEMPLATE_HELPER_HPP
#define ASMITH_REFLECTION_TEMPLATE_HELPER_HPP

namespace asmith {

	// Constant value comparison

	template<class T, T A, T B>
	struct template_value_comparison {
		typedef T type;
		enum : bool {
			LESS			= A < B,
			GREATER			= A > B,
			EQUAL			= A == B,
			NOT_EQUAL		= ! EQUAL,
			LESS_EQUAL		= LESS || EQUAL,
			GREATER_EQUAL	= GREATER || EQUAL
		};
	};

	// Type lists

	struct type_list_end {
		enum {
			SIZE = 0
		};
	};

	namespace implementation {
		template<class H, class T>
		struct type_list_ {
			typedef H head_t;
			typedef T tail_t;

			enum {
				SIZE = 1 + T::SIZE
			};
		};

		template<size_t I, class H, class ...TYPES>
		struct type_list__ {
			typedef type_list_<H,typename type_list__<I-1, TYPES...>::type> type;
		};

		template<class H, class ...TYPES>
		struct type_list__<1, H, TYPES...> {
			typedef type_list_<H, type_list_end> type;
		};
	}

	template<class ...TYPES>
	using type_list = typename implementation::type_list__<sizeof...(TYPES), TYPES...>::type;

	namespace implementation {
		template<size_t I, class LIST, class ENABLE = void>
		struct type_list_index_ {
			typedef typename type_list_index_<I-1, typename LIST::tail_t>::type type;
		};

		template<class LIST>
		struct type_list_index_<0, LIST> {
			typedef LIST type;
		};
	}

	template<size_t I, class LIST>
	using type_list_index = typename implementation::type_list_index_<I, LIST>::type;

	// Varadic template access

	namespace implementation {
		template<size_t I, class LIST, class ENABLE_ = void>
		struct type_at_index_ {
			typedef typename type_list_index<I, LIST>::head_t type;
		};

		template<size_t I, class LIST>
		struct type_at_index_<I, LIST, typename std::enable_if<template_value_comparison<size_t, I, LIST::SIZE>::GREATER_EQUAL>::type> {
			typedef void type;
		};
	}

	template<size_t I, class ...TYPES>
	using type_at_index = typename implementation::type_at_index_<I, type_list<TYPES...>>::type;
}
#endif