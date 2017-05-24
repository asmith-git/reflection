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
		R call(T& aObject, P1 p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2>
		R call(T& aObject, P1 p1, P2 p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3>
		R call(T& aObject, P1 p1, P2 p2, P3 p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(&aObject, &tmp, &p1);
			return tmp;
		}

		template<class R, class T, class P1, class P2, class P3, class P4, class P5>
		R call(T& aObject, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {
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
		R call_static(P1 p1) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2>
		R call_static(P1 p1, P2 p2) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3>
		R call_static(P1 p1, P2 p2, P3 p3) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3, class P4>
		R call_static(P1 p1, P2 p2, P3 p3, P4 p4) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		R call_static(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {
			//! \todo Check return and parameter types
			R tmp;
			call_unsafe(nullptr, &tmp, &p1);
			return tmp;
		}
	};

	template<class CLASS, class RETURN, class... PARAMS>
	class auto_reflection_function : public reflection_function {
	public:
		typedef RETURN(CLASS::*ptr_t)(PARAMS...);
		typedef RETURN(CLASS::*const_ptr_t)(PARAMS...) const;
		typedef RETURN(*static_ptr_t)(PARAMS...);
	private:
		const std::string mName;
		const ptr_t mPtr;
		const const_ptr_t mConstPtr;
		const static_ptr_t mStaticPtr;
		const size_t mModifiers;

		template<class R>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			if(mPtr) ((obj).*(mPtr))();
			else if(mConstPtr) ((obj).*(mConstPtr))();
			else if(mStaticPtr) mStaticPtr();
		}

		template<class R, class P1>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			if(mPtr) ((obj).*(mPtr))(p1);
			else if(mConstPtr) ((obj).*(mConstPtr))(p1);
			else if(mStaticPtr) mStaticPtr(p1);
		}

		template<class R, class P1, class P2>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			if(mPtr) ((obj).*(mPtr))(p1, p2);
			else if(mConstPtr) ((obj).*(mConstPtr))(p1, p2);
			else if(mStaticPtr) mStaticPtr(p1, p2);
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			if(mPtr) ((obj).*(mPtr))(p1, p2, p3);
			else if(mConstPtr) ((obj).*(mConstPtr))(p1, p2, p3);
			else if(mStaticPtr) mStaticPtr(p1, p2, p3);
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			if(mPtr) ((obj).*(mPtr))(p1, p2, p3, p4);
			else if(mConstPtr) ((obj).*(mConstPtr))(p1, p2, p3, p4);
			else if(mStaticPtr) mStaticPtr(p1, p2, p3, p4);
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			P5 p5 = asmith::get_parameter<P5>(aParams);
			if(mPtr) ((obj).*(mPtr))(p1, p2, p3, p4, p5);
			else if(mConstPtr) ((obj).*(mConstPtr))(p1, p2, p3, p4, p5);
			else if(mStaticPtr) mStaticPtr(p1, p2, p3, p4, p5);
		}

		template<class R>
		typename std::enable_if<! std::is_same<R,void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			if(mPtr) ret = ((obj).*(mPtr))();
			else if(mConstPtr) ret = ((obj).*(mConstPtr))();
			else if(mStaticPtr) ret = mStaticPtr();
		}

		template<class R, class P1>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			if (mPtr) ret = ((obj).*(mPtr))(p1);
			else if(mConstPtr) ret = ((obj).*(mConstPtr))(p1);
			else if(mStaticPtr) ret = mStaticPtr(p1);
		}

		template<class R, class P1, class P2>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			if(mPtr) ret = ((obj).*(mPtr))(p1, p2);
			else if(mConstPtr) ret = ((obj).*(mConstPtr))(p1, p2);
			else if(mStaticPtr) ret = mStaticPtr(p1, p2);
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			if(mPtr) ret = ((obj).*(mPtr))(p1, p2, p3);
			else if(mConstPtr) ret = ((obj).*(mConstPtr))(p1, p2, p3);
			else if(mStaticPtr) ret = mStaticPtr(p1, p2, p3);
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			if(mPtr) ret = ((obj).*(mPtr))(p1, p2, p3, p4);
			else if(mConstPtr) ret = ((obj).*(mConstPtr))(p1, p2, p3, p4);
			else if(mStaticPtr) ret = mStaticPtr(p1, p2, p3, p4);
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<!std::is_same<R, void>::value, void>::type call__(void* aObject, void* aReturn, void* aParams) const {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			R& ret = *reinterpret_cast<RETURN*>(aReturn);
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			P5 p5 = asmith::get_parameter<P5>(aParams);
			if(mPtr) ret = ((obj).*(mPtr))(p1, p2, p3, p4, p5);
			else if(mConstPtr) ret = ((obj).*(mConstPtr))(p1, p2, p3, p4, p5);
			else if(mStaticPtr) ret = mStaticPtr(p1, p2, p3, p4, p5);
		}
	public:
		auto_reflection_function(const std::string& aName, const ptr_t aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPtr(aPtr),
			mConstPtr(nullptr),
			mStaticPtr(nullptr)
		{}

		auto_reflection_function(const std::string& aName, const const_ptr_t aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPtr(nullptr),
			mConstPtr(aPtr),
			mStaticPtr(nullptr)
		{}

		auto_reflection_function(const std::string& aName, const static_ptr_t aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPtr(nullptr),
			mConstPtr(nullptr),
			mStaticPtr(aPtr)
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
}

#endif