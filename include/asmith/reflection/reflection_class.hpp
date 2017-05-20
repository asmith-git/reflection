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

#include <type_traits>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#ifndef ASMITH_REFLECTION_CLASS_HPP
#define ASMITH_REFLECTION_CLASS_HPP

namespace asmith {
	
	class reflection_variable;
	class reflection_function;
	class reflection_constructor;
	class reflection_destructor;
	
	class reflection_class {
	public:
		virtual ~reflection_class() {}
		
		virtual const char* get_name() const = 0;
		virtual size_t get_size() const = 0;
		virtual size_t get_variable_count() const = 0;
		virtual const reflection_variable& get_variable(size_t) const = 0;
		virtual size_t get_function_count() const = 0;
		virtual const reflection_function& get_function(size_t) const = 0;
		virtual size_t get_constructor_count() const = 0;
		virtual const reflection_constructor& get_constructor(size_t) const = 0;
		virtual const reflection_destructor& get_destructor() const = 0;
		virtual size_t get_parent_count() const = 0;
		virtual const reflection_class& get_parent_class(size_t) const = 0;
	};

	template<class T>
	const reflection_class& reflect() {
		throw std::runtime_error("asmith::reflect : Reflection not defined for this type");
	}

	namespace implementation {
		class auto_reflection_class_ : public reflection_class {
		protected:
			std::vector<const reflection_class*> mParents;
			std::vector<std::shared_ptr<reflection_constructor>> mConstructors;
			std::vector<std::shared_ptr<reflection_variable>> mVariables;
			std::vector<std::shared_ptr<reflection_function>> mFunctions;
			std::shared_ptr<reflection_destructor> mDestructor;
			const std::string mName;
			const size_t mSize;

			template<class C, class RETURN, class... PARAMS>
			struct function_ptr {
				typedef RETURN(C::*type)(PARAMS...);
			};

			template<class C, class T>
			struct variable_ptr {
				typedef T(C::*type);
			};
		public:
			auto_reflection_class_(const std::string& aName, const size_t aSize) :
				mName(aName),
				mSize(aSize)
			{}

			virtual ~auto_reflection_class_() {

			}

			// Inherited from reflection_class

			const char* get_name() const override {
				return mName.c_str();
			}

			size_t get_size() const override {
				return mSize;
			}

			size_t get_variable_count() const override {
				return mVariables.size();
			}

			const reflection_variable& get_variable(size_t aIndex) const override {
				return *mVariables[aIndex];
			}

			size_t get_function_count() const override {
				return mFunctions.size();
			}

			const reflection_function& get_function(size_t aIndex) const override {
				return *mFunctions[aIndex];
			}

			size_t get_constructor_count() const override {
				return mConstructors.size();
			}

			const reflection_constructor& get_constructor(size_t aIndex) const override {
				return *mConstructors[aIndex];
			}

			const reflection_destructor& get_destructor() const override {
				return *mDestructor;
			}

			size_t get_parent_count() const override {
				return mParents.size();
			}

			const reflection_class& get_parent_class(size_t aIndex) const override {
				return *mParents[aIndex];
			}
		};
	}

	template<class CLASS>
	class auto_reflection_class : public implementation::auto_reflection_class_ {
	public:
		auto_reflection_class(const std::string& aName) :
			auto_reflection_class_(aName, sizeof(CLASS))
		{}

		auto_reflection_class(const std::string& aName, const size_t aSize) :
			auto_reflection_class_(aName, aSize)
		{}

		//! \todo Add constructors, variables and destructor

		template<class PARENT>
		auto_reflection_class& parent() {
			mFunctions.push_back(&reflect<PARENT>());
			return *this;
		}

		template<class T>
		auto_reflection_class& variable(const std::string& aName, typename variable_ptr<CLASS, T>::type aPtr, const size_t aModifiers) {
			mVariables.push_back(std::shared_ptr<reflection_variable>(
				new auto_reflection_variable<CLASS, T>(aName, aPtr, aModifiers)
			));
			return *this;
		}

		template<class RETURN, class... PARAMS>
		auto_reflection_class& function(const std::string& aName, typename function_ptr<CLASS, RETURN, PARAMS...>::type aPtr, const size_t aModifiers) {
			mFunctions.push_back(std::shared_ptr<reflection_function>(
				new auto_reflection_function<CLASS, RETURN, PARAMS...>(aName, aPtr, aModifiers)
			));
			return *this;
		}
	};

	template<>
	class auto_reflection_class<void> : public reflection_class {
	public:
		// Inherited from reflection_class

		const char* get_name() const override {
			return "void";
		}

		size_t get_size() const override {
			return 0;
		}

		size_t get_variable_count() const override {
			return 0;
		}

		const reflection_variable& get_variable(size_t aIndex) const override {
			throw std::runtime_error("asmith::reflection_class::get_variable : Type is void");
		}

		size_t get_function_count() const override {
			return 0;
		}

		const reflection_function& get_function(size_t aIndex) const override {
			throw std::runtime_error("asmith::get_function::get_variable : Type is void");
		}

		size_t get_constructor_count() const override {
			return 0;
		}

		const reflection_constructor& get_constructor(size_t aIndex) const override {
			throw std::runtime_error("asmith::get_function::get_constructor : Type is void");
		}

		const reflection_destructor& get_destructor() const override {
			throw std::runtime_error("asmith::get_function::get_destructor : Type is void");
		}

		size_t get_parent_count() const override {
			return 0;
		}

		const reflection_class& get_parent_class(size_t aIndex) const override {
			throw std::runtime_error("asmith::get_function::get_parent_class : Type is void");
		}
	};

	template<>
	const reflection_class& reflect<void>() {
		static const auto_reflection_class<void> REFLECTION;
		return REFLECTION;
	}


#define ASMITH_REFLECTION_PRIMATIVE_REFLECT(aName)\
	template<>\
	const reflection_class& reflect<aName>() {\
		static const auto_reflection_class<aName> REFLECTION(#aName);\
		return REFLECTION;\
	}

	ASMITH_REFLECTION_PRIMATIVE_REFLECT(bool)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(char)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(uint8_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(uint16_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(uint32_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(uint64_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(int8_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(int16_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(int32_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(int64_t)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(float)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(double)
}
#endif