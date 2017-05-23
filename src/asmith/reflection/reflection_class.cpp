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

#include "asmith/reflection/reflection_class.hpp"
#include <map>
#include <mutex>
#include "asmith/reflection/reflection_constructor.hpp"
#include "asmith/reflection/reflection_function.hpp"
#include "asmith/reflection/reflection_variable.hpp"

	
namespace asmith {
	std::map<std::string, const reflection_class*> REFLECTION_CLASS_MAP;
	std::mutex REFLECTION_CLASS_MAP_LOCK;

	// reflection_class

	void reflection_class::register_class(const reflection_class& aClass) throw() {
		REFLECTION_CLASS_MAP_LOCK.lock();
			REFLECTION_CLASS_MAP.emplace(aClass.get_name(), &aClass);
		REFLECTION_CLASS_MAP_LOCK.unlock();
	}

	const reflection_class& reflection_class::get_class_by_name(const char* aName) {
		const reflection_class* tmp = nullptr;
		REFLECTION_CLASS_MAP_LOCK.lock();
			const auto i = REFLECTION_CLASS_MAP.find(aName);
			if(i != REFLECTION_CLASS_MAP.end()) tmp = i->second;
		REFLECTION_CLASS_MAP_LOCK.unlock();
		if(tmp == nullptr) return INVALID_REFLECTION_CLASS;
		return *tmp;
	}

	const reflection_constructor& reflection_class::get_trivial_constructor() const {
		const size_t s = get_constructor_count();
		for(size_t i = 0; i < s; ++i) {
			const reflection_constructor& con = get_constructor(i);
			if(con.get_parameter_count() == 0) return con;
		}
		throw std::runtime_error("asmith::reflection_class::get_trivial_constructor : Class does not have a trivial constructor");
	}

	const reflection_function& reflection_class::get_function(const char* aName) const {
		//! \todo Handle overloaded functions

		const size_t s = get_function_count();
		for (size_t i = 0; i < s; ++i) {
			const reflection_function& fun = get_function(i);
			if(strcmp(fun.get_name(), aName) == 0) return fun;
		}
		throw std::runtime_error("asmith::reflection_class::get_function : Class does not have function with name");
	}

	const reflection_variable& reflection_class::get_variable(const char* aName) const {
		//! \todo Handle overloaded functions

		const size_t s = get_variable_count();
		for (size_t i = 0; i < s; ++i) {
			const reflection_variable& var = get_variable(i);
			if (strcmp(var.get_name(), aName) == 0) return var;
		}
		throw std::runtime_error("asmith::reflection_class::get_variable : Class does not have variable with name");
	}
}