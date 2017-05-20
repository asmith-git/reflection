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

		template<class R, class T>
		R call(T& aObject) const {
			//! \todo Check return type
			R tmp;
			call_(&aObject, &tmp, nullptr);
			return tmp;
		}

		template<class R, class T, class P1>
		R call(T& aObject, P1 p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2>
		R call(T& aObject, P1 p1, P2 p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3>
		R call(T& aObject, P1 p1, P2 p2, P3 p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4, class P5>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {
			//! \todo Check return and parameter types
			R tmp;
			call_(&aObject, &tmp, &p1);
			return tmp;
		}
	};

	template<class CLASS, class RETURN, class... PARAMS>
	class auto_reflection_function : public reflection_function {
	public:
		typedef RETURN(CLASS::*ptr_t)(PARAMS...);
	private:
		const std::string mName;
		const ptr_t mPointer;
		const size_t mModifiers;

		template<class R>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			((obj).*(mPointer))();
		}

		template<class R, class P1>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			((obj).*(mPointer))(*p1);
		}

		template<class R, class P1, class P2>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			((obj).*(mPointer))(*p1, *p2);
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			((obj).*(mPointer))(*p1, *p2, *p3);
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			((obj).*(mPointer))(*p1, *p2, *p3, *p4);
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			const P5* const p3 = reinterpret_cast<const P5*>(reinterpret_cast<const uint8_t*>(p4) + sizeof(P4));
			((obj).*(mPointer))(*p1, *p2, *p3, *p4, *p5);
		}

		template<class R>
		typename std::enable_if<! std::is_same<R,void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			ret = ((obj).*(mPointer))();
		}

		template<class R, class P1>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			ret = ((obj).*(mPointer))(*p1);
		}

		template<class R, class P1, class P2>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			ret = ((obj).*(mPointer))(*p1, *p2);
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			ret = ((obj).*(mPointer))(*p1, *p2, *p3);
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			ret = ((obj).*(mPointer))(*p1, *p2, *p3, *p4);
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, const void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			const P5* const p3 = reinterpret_cast<const P5*>(reinterpret_cast<const uint8_t*>(p4) + sizeof(P4));
			ret = ((obj).*(mPointer))(*p1, *p2, *p3, *p4, *p5);
		}
	protected:
		// Inherited from reflection_function
		void call_(void* aObject, void* aReturn, const void* aParams) const override {
			call__<RETURN, PARAMS...>(aObject, aReturn, aParams);
		}
	public:
		auto_reflection_function(const std::string& aName, const ptr_t aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPointer(aPtr)
		{}

		// Inherited from reflection_function
		const char* get_name() const override {
			return mName.c_str();
		}

		size_t get_parameter_count() const override {
			return sizeof...(PARAMS);
		}

		const reflection_class& get_parameter(size_t aIndex) const override {
			switch(aIndex) {
			case 0: return reflect<type_at_index<0, PARAMS...>::type>();
			case 1: return reflect<type_at_index<1, PARAMS...>::type>();
			case 2: return reflect<type_at_index<2, PARAMS...>::type>();
			case 3: return reflect<type_at_index<3, PARAMS...>::type>();
			case 4: return reflect<type_at_index<4, PARAMS...>::type>();
			case 5: return reflect<type_at_index<5, PARAMS...>::type>();
			}
		};

		const reflection_class& get_return() const override {
			return reflect<RETURN>();
		};

		size_t get_modifiers() const override {
			return mModifiers;
		};
	};
}

#endif