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

#include <cstdint>

namespace asmith {
	class reflection_class;

	class reflection_variable {
	public:
		virtual ~reflection_variable() {}
		
		virtual const reflection_class& get_class() const = 0;
		virtual const char* get_name() const = 0;
		virtual uint32_t get_modifiers() const = 0;

		virtual void set_unsafe(void*, const void*) const = 0;
		virtual void get_unsafe(const void*, void*) const = 0;

		template<class CLASS, class T>
		void set(CLASS& aObject, T aValue) const {
			//! \todo Check type
			set_unsafe(&aObject, &aValue);
		}

		template<class CLASS, class T>
		T get(const CLASS& aObject, T aValue) const {
			//! \todo Check type
			T tmp;
			get_unsafe(&aObject, &tmp);
			return tmp;
		}
	};

	template<class CLASS, class T>
	class auto_reflection_variable : public reflection_variable {
	public:
		typedef T(CLASS::*ptr_t);
	private:
		const std::string mName;
		const ptr_t mPointer;
		const size_t mModifiers;
	protected:
		// Inherited from reflection_variable

		void set_unsafe(void* aObject, const void* aValue) const override {
			CLASS& obj = *reinterpret_cast<CLASS*>(aObject);
			const T& val = *reinterpret_cast<const T*>(aValue);
			((obj).*(mPointer)) = val;
		}

		void get_unsafe(const void* aObject, void* aValue) const override {
			const CLASS& obj = *reinterpret_cast<const CLASS*>(aObject);
			T& val = *reinterpret_cast<T*>(aValue);
			val = ((obj).*(mPointer));
		}

	public:
		auto_reflection_variable(const std::string& aName, const ptr_t aPtr, const size_t aModifiers) :
			mName(aName),
			mModifiers(aModifiers),
			mPointer(aPtr)
		{}

		// Inherited from reflection_function

		const char* get_name() const override {
			return mName.c_str();
		}

		const reflection_class& get_class() const override {
			return reflect<T>();
		};

		size_t get_modifiers() const override {
			return mModifiers;
		};
	};
}

#endif