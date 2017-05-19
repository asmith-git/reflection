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

#ifndef ASMITH_REFLECTION_CLASS_HPP
#define ASMITH_REFLECTION_CLASS_HPP

namespace asmith {
	
	class reflection_variable;
	class reflection_function;
	class reflection_constructor;
	class reflection_destructor;
	
	class reflection_class {
	public:
		virtual ~reflection_class() {}
		
		virtual const char* get_name() const = 0;
		virtual size_t get_size() const = 0;
		virtual size_t get_variable_count() const = 0;
		virtual const reflection_variable& get_variable(size_t) const = 0;
		virtual size_t get_function_count() const = 0;
		virtual const reflection_function& get_function(size_t) const = 0;
		virtual size_t get_constructor_count() const = 0;
		virtual const reflection_constructor& get_constructor(size_t) const = 0;
		virtual const reflection_destructor& get_destructor() const = 0;
		virtual size_t get_parent_count() const = 0;
		virtual const reflection_class& get_parent_class(size_t) const = 0;
	};

	template<class C, class T>
	using reflection_variable_ptr = T C::*;
}
#endif