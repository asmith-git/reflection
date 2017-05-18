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

#ifndef ASMITH_REFLECTION_VARIABLE_HPP
#define ASMITH_REFLECTION_VARIABLE_HPP

namespace asmith {
	class reflection_class;

	class reflection_variable {
	public:
		virtual ~reflection_variable() {}
		
		virtual const reflection_class& get_class() const = 0;
		virtual const char* get_name() const = 0;
		virtual uint32_t get_modifiers() const = 0;
		virtual void set(void*, const void*) const = 0;
		virtual void get(const void*, void*) const = 0;
	};
}

#endif