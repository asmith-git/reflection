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

#ifndef ASMITH_REFLECTION_INSTANCE_HPP
#define ASMITH_REFLECTION_INSTANCE_HPP

#include "reflection_class.hpp"
#include "reflection_constructor.hpp"
#include "reflection_destructor.hpp"
#include "reflection_function.hpp"
#include "reflection_variable.hpp"
#include "reflection_modifier.hpp"

namespace asmith {
	class reflection_instance {
	private:
		const reflection_class* mClass;
		void* mData;

		reflection_instance& operator=(reflection_instance&&) = delete;
		reflection_instance& operator=(const reflection_instance&) = delete;
	public:
		reflection_instance();
		reflection_instance(reflection_instance&&);
		reflection_instance(const reflection_instance&);
		~reflection_instance();

		reflection_instance call_unsafe(const char*, void*);
		const reflection_class& get_class() const;
		void* as_unsafe();
		const void* as_unsafe() const;

		template<class ...PARAMS>
		reflection_instance(const reflection_class& aClass, PARAMS... aParams) :
			mClass(&aClass),
			mData(operator new(aClass.get_size()))
		{
			//! \todo Check argument types
			const size_t s = aClass.get_constructor_count();
			for(size_t i = 0; i < s; ++i) {
				const reflection_constructor& con = aClass.get_constructor(i);
				if(con.get_parameter_count() == sizeof...(PARAMS)) {
					con.call(mData, aParams...);
					return;
				}
			}
			throw std::runtime_error("asmith::reflection_instance : No constructor with parameter count");
		}

		template<class R, class ...PARAMS>
		R call(const char* aName, PARAMS... aParams) {
			//! \todo Handle overloaded functions
			return mClass->get_function(aName).call<R, int, PARAMS...>(*reinterpret_cast<int*>(mData));
		}

		template<class T>
		T get_variable(const char* aName) {
			return mClass->get_variable(aName).get<T>();
		}

		template<class T>
		void set_variable(const char* aName, T aValue) {
			return mClass->get_variable(aName).set<T>(aValue);
		}

		template<class T>
		T& as() {
			if(strcmp(mClass->get_name(), reflect<T>().get_name()) != 0) throw std::runtime_error("asmith::reflection_instance::as : Type mismatch");
			return *reinterpret_cast<T*>(mData);
		}

		template<class T>
		const T& as() const {
			if(strcmp(mClass->get_name(), reflect<T>().get_name()) != 0) throw std::runtime_error("asmith::reflection_instance::as : Type mismatch");
			return *reinterpret_cast<const T*>(mData);
		}
	};
}

#endif