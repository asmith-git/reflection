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

#ifndef ASMITH_REFLECTION_MASTER_HPP
#define ASMITH_REFLECTION_MASTER_HPP

#include "reflection_class.hpp"
#include "reflection_constructor.hpp"
#include "reflection_destructor.hpp"
#include "reflection_function.hpp"
#include "reflection_variable.hpp"
#include "reflection_modifier.hpp"

namespace asmith {
	class reflection_test {
	private:
		std::string name;
		int dimensions;
		float lower_bound;
		float upper_bound;
	public:
		std::string get_name() { return name; }
		int get_dimensions() { return dimensions; }
		float get_lower_bound() { return lower_bound; }
		float get_upper_bound() { return upper_bound; }

		#define ASMITH_REFLECTION_CLASS_NAME reflection_test
		#define ASMITH_REFLECTION_VARIABLE_COUNT 4
		#define ASMITH_REFLECTION_CONSTRUCTOR_COUNT 0
		#define ASMITH_REFLECTION_FUNCTION_COUNT 0
		#define ASMITH_REFLECTION_PARENT_COUNT 0
		ASMITH_BEGIN_REFLECTION
			const asmith::reflection_function& get_function(size_t) const override { throw 0; }
			const asmith::reflection_constructor& get_constructor(size_t) const override { throw 0; }
			const reflection_class& get_parent_class(size_t) const override { throw 0; }

			ASMITH_REFLECTION_DESTRUCTOR(REFLECTION_PUBLIC)

			ASMITH_BEGIN_REFLECTION_VARIABLES
				ASMITH_REFLECTION_VARIABLE(name,		REFLECTION_PRIVATE);
				ASMITH_REFLECTION_VARIABLE(dimensions,	REFLECTION_PRIVATE);
				ASMITH_REFLECTION_VARIABLE(lower_bound,	REFLECTION_PRIVATE);
				ASMITH_REFLECTION_VARIABLE(upper_bound,	REFLECTION_PRIVATE);
			ASMITH_END_REFLECTION_VARIABLES
		ASMITH_END_REFLECTION

		#undef ASMITH_REFLECTION_CLASS_NAME
		#undef ASMITH_REFLECTION_VARIABLE_COUNT
		#undef ASMITH_REFLECTION_CONSTRUCTOR_COUNT
		#undef ASMITH_REFLECTION_FUNCTION_COUNT
		#undef ASMITH_REFLECTION_PARENT_COUNT
	};
}

#endif