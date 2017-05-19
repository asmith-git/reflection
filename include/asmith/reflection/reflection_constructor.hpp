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

#ifndef ASMITH_REFLECTION_CONSTRUCTOR_HPP
#define ASMITH_REFLECTION_CONSTRUCTOR_HPP

namespace asmith {
	
	class reflection_class;
	
	class reflection_constructor {
	public:
		virtual ~reflection_constructor() {}
		
		virtual size_t get_parameter_count() const = 0;
		virtual const reflection_class& get_parameter(size_t) const = 0;
		virtual size_t get_modifiers() const = 0;
		virtual void call(void*, const void*) const = 0;
	};
}

#endif