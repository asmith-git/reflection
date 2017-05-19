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

#ifndef ASMITH_REFLECTION_FUNCTION_HPP
#define ASMITH_REFLECTION_FUNCTION_HPP

#include <string>

namespace asmith {
	
	class reflection_class;
	
	class reflection_function {
	protected:
		virtual void call_(void*, void*, const void*) const = 0;
	public:
		virtual ~reflection_function() {}
		
		virtual const char* get_name() const = 0;
		virtual size_t get_parameter_count() const = 0;
		virtual const reflection_class& get_parameter(size_t) const = 0;
		virtual const reflection_class& get_return() const = 0;
		virtual size_t get_modifiers() const = 0;

		template<class T, class R>
		R call(T& aObject) const {
			//! \todo Check return type
			R tmp;
			call_(&aObject, &tmp, nullptr);
			return tmp;
		}

		template<class T, class R, class P1>
		R call(T& aObject, P1 p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class T, class R, class P1, class P2>
		R call(T& aObject, P1 p1, P2 p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class T, class R, class P1, class P2, class P3>
		R call(T& aObject, P1 p1, P2 p2, P3 p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class T, class R, class P1, class P2, class P3, class P4>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class T, class R, class P1, class P2, class P3, class P4, class P5>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}
	};

	template<class CLASS, class RETURN, class... PARAMS>
	class auto_reflection_function : public reflection_function {
	private:
		const std::string mName;
		const size_t mModifiers;
	protected:
		// Inherited from reflection_function
		void call_(void* aObject, void* aReturn, const void* aParams) const override {
			//! \todo Implement
			throw 0;
		}
	public:
		auto_reflection_function(const std::string& aName, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers)
		{}

		// Inherited from reflection_function
		const char* get_name() const override {
			return mName.c_str();
		}

		size_t get_parameter_count() const override {
			return sizeof...(PARAMS);
		}

		const reflection_class& get_parameter(size_t aIndex) const override {
			//! \todo Implement
			throw 0;
		};

		const reflection_class& get_return() const override {
			//! \todo Implement
			throw 0;
		};

		size_t get_modifiers() const override {
			return mModifiers;
		};
	};
}

#endif