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

#ifndef ASMITH_REFLECTION_CLASS_HPP
#ifndef ASMITH_REFLECTION_CLASS_HPP

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
		
//		virtual const reflection_constructor& get_trivial_constructor() const{
//			const size_t s = get_constructor_count();
//			for(size_t i = 0; i < s; ++i) {
//				const reflection_constructor& c = get_constructor(i);
//				if(c.get_parameter_count() == 0) return c;
//			}
//			throw std::runtime_error("asmith::reflection_class::get_trivial_constructor : Class does not contain a trivial constructor");
//		}
	};
	
	namespace implementation {
		template<class T, class ENABLE = void>
		struct reflection_class {
			typedef void type;
		}
	}
	
	template<class T>
	static const reflection_class& get_reflection_class() {
		static typename implementation::reflection_class::type REFLECTION_CLASS;
		return REFLECTION_CLASS;
	}
}

#endif