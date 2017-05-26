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
#include "template_helper.hpp"

namespace asmith {

	//! \todo Handle reference as return
	
	class reflection_class;
	
	class reflection_function {
	public:
		virtual ~reflection_function() {}
		
		virtual const char* get_name() const = 0;
		virtual size_t get_parameter_count() const = 0;
		virtual const reflection_class& get_parameter(size_t) const = 0;
		virtual const reflection_class& get_return() const = 0;
		virtual size_t get_modifiers() const = 0;

		virtual void call_unsafe(void*, void*, void*) const = 0;

		template<class R, class T>
		R call(T& aObject) const {
			//! \todo Check return type
			R tmp;
			call_unsafe(&aObject, &tmp, nullptr);
			return tmp;
		}

		template<class R, class T, class P1>
		R call(T& aObject, reflection_parameter_map<P1> p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2>
		R call(T& aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3>
		R call(T& aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4>
		R call(T& aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4, class P5>
		R call(T& aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4, reflection_parameter_map<P5> p5) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R>
		R call_static() const {
			R tmp;
			call_unsafe(nullptr, &tmp, nullptr);
			return tmp;
		}

		template<class R, class P1>
		R call_static(reflection_parameter_map<P1> p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2>
		R call_static(reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3>
		R call_static(reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3, class P4>
		R call_static(reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		R call_static(reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4, reflection_parameter_map<P5> p5) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}
	};

	namespace implementation {
		template<class CLASS, class RETURN, class ...PARAMS>
		struct reflection_function_dispatch {
			typedef RETURN(CLASS::*ptr_t)(PARAMS...);
			typedef RETURN(CLASS::*const_ptr_t)(PARAMS...) const;
			typedef RETURN(*static_ptr_t)(PARAMS...);

			static inline void execute(CLASS* const aObject, RETURN* aReturn, ptr_t aPtr, PARAMS... aParams) {
				*aReturn = ((aObject)->*(aPtr))(aParams...);
			}

			static inline void execute(CLASS* const aObject, RETURN* aReturn, const_ptr_t aPtr, PARAMS... aParams) {
				*aReturn = ((aObject)->*(aPtr))(aParams...);
			}

			static inline void execute(CLASS* const aObject, RETURN* aReturn, static_ptr_t aPtr, PARAMS... aParams) {
				*aReturn = aPtr(aParams...);
			}
		};

		template<class CLASS, class ...PARAMS>
		struct reflection_function_dispatch<CLASS, void, PARAMS...> {
			typedef void(CLASS::*ptr_t)(PARAMS...);
			typedef void(CLASS::*const_ptr_t)(PARAMS...) const;
			typedef void(*static_ptr_t)(PARAMS...);

			static inline void execute(CLASS* const aObject, void* aReturn, ptr_t aPtr, PARAMS... aParams) {
				((aObject)->*(aPtr))(aParams...);
			}

			static inline void execute(CLASS* const aObject, void* aReturn, const_ptr_t aPtr, PARAMS... aParams) {
				((aObject)->*(aPtr))(aParams...);
			}

			static inline void execute(CLASS* const aObject, void* aReturn, static_ptr_t aPtr, PARAMS... aParams) {
				aPtr(aParams...);
			}
		};
	}

	template<class CLASS, class FUNCTION, class RETURN, class... PARAMS>
	class auto_reflection_function : public reflection_function {
	private:
		const std::string mName;
		const size_t mModifiers;
		const FUNCTION mPtr;

		template<class R>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr);
		}

		template<class R, class P1>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			auto p1 = asmith::get_parameter<P1>(aParams);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr, p1);
		}

		template<class R, class P1, class P2>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			auto p1 = asmith::get_parameter<P1>(aParams);
			auto p2 = asmith::get_parameter<P2>(aParams);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr, p1, p2);
		}

		template<class R, class P1, class P2, class P3>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			auto p1 = asmith::get_parameter<P1>(aParams);
			auto p2 = asmith::get_parameter<P2>(aParams);
			auto p3 = asmith::get_parameter<P3>(aParams);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr, p1, p2, p3);
		}

		template<class R, class P1, class P2, class P3, class P4>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			auto p1 = asmith::get_parameter<P1>(aParams);
			auto p2 = asmith::get_parameter<P2>(aParams);
			auto p3 = asmith::get_parameter<P3>(aParams);
			auto p4 = asmith::get_parameter<P4>(aParams);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr, p1, p2, p3, p4);
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		void call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS* const obj = reinterpret_cast<CLASS*>(aObject);
			R* const ret = reinterpret_cast<RETURN*>(aReturn);
			auto p1 = asmith::get_parameter<P1>(aParams);
			auto p2 = asmith::get_parameter<P2>(aParams);
			auto p3 = asmith::get_parameter<P3>(aParams);
			auto p4 = asmith::get_parameter<P4>(aParams);
			auto p5 = asmith::get_parameter<P5>(aParams);
			implementation::reflection_function_dispatch<CLASS, RETURN, PARAMS...>::execute(obj, ret, mPtr, p1, p2, p3, p4, p5);
		}

	public:
		auto_reflection_function(const std::string& aName, const FUNCTION aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPtr(aPtr)
		{}

		// Inherited from reflection_function
		const char* get_name() const override {
			return mName.c_str();
		}

		size_t get_parameter_count() const override {
			return sizeof...(PARAMS);
		}

		const reflection_class& get_parameter(size_t aIndex) const override {
			return reflect_type_at<PARAMS...>(aIndex);
		}

		const reflection_class& get_return() const override {
			return reflect<RETURN>();
		}

		size_t get_modifiers() const override {
			return mModifiers;
		}

		void call_unsafe(void* aObject, void* aReturn, void* aParams) const override {
			call__<RETURN, PARAMS...>(aObject, aReturn, aParams);
		}
	};

	template<class CLASS, class RETURN, class... PARAMS>
	using member_reflection_function = auto_reflection_function<CLASS, RETURN, RETURN(CLASS::*)(PARAMS...), PARAMS...>;

	template<class CLASS, class RETURN, class... PARAMS>
	using const_member_reflection_function = auto_reflection_function<CLASS, RETURN, RETURN(CLASS::*)(PARAMS...) const, PARAMS...>;

	template<class CLASS, class RETURN, class... PARAMS>
	using static_reflection_function = auto_reflection_function<CLASS, RETURN, RETURN(*)(PARAMS...), PARAMS...>;
}

#endif