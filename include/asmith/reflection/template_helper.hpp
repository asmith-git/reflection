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

	template<size_t I, class ...TYPES>
	class type_at_index {
	private:
		template<size_t I, bool CHECK, class ...TYPES>
		struct type_at_index_ {
			typedef decltype(std::get<I>(std::tuple<TYPES...>())) type;
		};

		template<size_t I, class ...TYPES>
		struct type_at_index_<I, false, TYPES...> {
			typedef void type;
		};
	public:
		typedef typename type_at_index_<I, template_value_comparison<size_t, I, sizeof...(TYPES)>::LESS, TYPES...>::type type;
	};
}
#endif