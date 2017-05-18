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
		
//		virtual const reflection_constructor& get_trivial_constructor() const{
//			const size_t s = get_constructor_count();
//			for(size_t i = 0; i < s; ++i) {
//				const reflection_constructor& c = get_constructor(i);
//				if(c.get_parameter_count() == 0) return c;
//			}
//			throw std::runtime_error("asmith::reflection_class::get_trivial_constructor : Class does not contain a trivial constructor");
//		}
	};
	
	namespace implementation {

		template<class T>
		class primative_reflection_class : public asmith::reflection_class {
		public:
			const char* get_name() const override { return ""; } //! \todo Name
			size_t get_size() const override { return sizeof(T); }
			size_t get_variable_count() const override { return 0; }
			const reflection_variable& get_variable(size_t) const override { throw std::runtime_error(""); }
			size_t get_function_count() const override { return 0; }
			const reflection_function& get_function(size_t) const override { throw std::runtime_error(""); }
			size_t get_parent_count() const override { return 0; }
			const reflection_class& get_parent_class(size_t) const override { throw std::runtime_error(""); }
			size_t get_constructor_count() const override { return 2; }
			const reflection_constructor& get_constructor(size_t i) const override { 
				class trivial_constructor : public reflection_constructor {
				public:
					size_t get_parameter_count() const override { return 0; }
					const reflection_class& get_parameter(size_t) const override { throw std::runtime_error(""); }
					size_t get_modifiers() const override { return REFLECTION_PUBLIC; }
					void call(void* aObject, const void* aParams) const override { new(aObject) T(); }
				};
				class copy_constructor : public reflection_constructor {
				public:
					size_t get_parameter_count() const override { return 1; }
					const reflection_class& get_parameter(size_t i) const override { if(i == 0) return get_reflection_class<T>(); else throw std::runtime_error(""); }
					size_t get_modifiers() const override { return REFLECTION_PUBLIC; }
					void call(void* aObject, const void* aParams) const override { new(aObject) T(*static_cast<const T*>(aParams)); }
				};

				static trivial_constructor TRIVIAL_CONSTRUCTOR;
				static copy_constructor COPY_CONSTRUCTOR;

				switch (i) {
					case 0: return TRIVIAL_CONSTRUCTOR;
					case 1: return COPY_CONSTRUCTOR;
					default: throw std::runtime_error("");
				}
			}
			const reflection_destructor& get_destructor() const override {
				class destructor : public reflection_destructor {
				public:
					size_t get_modifiers() const override { return REFLECTION_PUBLIC; }
					void call(void* aObject) const override { static_cast<T*>(aObject)->~T(); }
				};
				static destructor DESTRUCTOR;
				return DESTRUCTOR;
			}
		};

		template<class T, class ENABLE = void>
		struct reflection_class {
			typedef void type;
		};

		template<class T>
		struct reflection_class<T, typename std::enable_if<
			std::is_same<T, bool>::value ||
			std::is_same<T, char>::value ||
			std::is_same<T, uint8_t>::value ||
			std::is_same<T, uint16_t>::value ||
			std::is_same<T, uint32_t>::value ||
			std::is_same<T, uint64_t>::value ||
			std::is_same<T, int8_t>::value ||
			std::is_same<T, int16_t>::value ||
			std::is_same<T, int32_t>::value ||
			std::is_same<T, int64_t>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||
			std::is_same<T, std::string>::value
		>::type> {
			typedef primative_reflection_class<T> type;
		};
	}
	
	template<class T>
	static const reflection_class& get_reflection_class() {
		static typename implementation::reflection_class<T>::type REFLECTION_CLASS;
		return REFLECTION_CLASS;
	}

	template<class C, class T>
	using reflection_variable_ptr = T C::*;

#define MACRO_JOIN2(a, b) a##b
#define MACRO_JOIN(a, b) MACRO_JOIN2(a , b)
#define MACRO_STRING(a) #a

#define ASMITH_BEGIN_REFLECTION \
	class MACRO_JOIN(ASMITH_REFLECTION_CLASS_NAME,_reflection) : public asmith::reflection_class {\
	const char* get_name() const override { return MACRO_STRING(ASMITH_REFLECTION_CLASS_NAME); };\
	size_t get_size() const override { return sizeof(ASMITH_REFLECTION_CLASS_NAME); }\
	size_t get_variable_count() const override { return ASMITH_REFLECTION_VARIABLE_COUNT; }\
	size_t get_constructor_count() const override { return ASMITH_REFLECTION_CONSTRUCTOR_COUNT; }\
	size_t get_function_count() const override { return ASMITH_REFLECTION_FUNCTION_COUNT; }\
	size_t get_parent_count() const override { return ASMITH_REFLECTION_PARENT_COUNT; }
#define ASMITH_END_REFLECTION };

#define ASMITH_REFLECTION_VARIABLE(aName, aMods) \
	class MACRO_JOIN(aName,_var_class) : public asmith::reflection_variable {\
	public:\
		typedef decltype(ASMITH_REFLECTION_CLASS_NAME::aName) type;\
		const asmith::reflection_class& get_class() const override { return asmith::get_reflection_class<type>(); }\
		const char* get_name() const override { return MACRO_STRING(aName); }\
		uint32_t get_modifiers() const override { return aMods; }\
		void set(void* aObject, const void* aInput) const override { static_cast<ASMITH_REFLECTION_CLASS_NAME*>(aObject)->*&ASMITH_REFLECTION_CLASS_NAME::aName = *static_cast<const type*>(aInput); }\
		void get(const void* aObject, void* aOutput) const override { *static_cast<type*>(aOutput), static_cast<const ASMITH_REFLECTION_CLASS_NAME*>(aObject)->*&ASMITH_REFLECTION_CLASS_NAME::aName; }\
	};\
	static MACRO_JOIN(aName,_var_class) MACRO_JOIN(aName,_var);\
	if(i == currentVar) return MACRO_JOIN(aName,_var);\
	++currentVar;


#define ASMITH_BEGIN_REFLECTION_VARIABLES const asmith::reflection_variable& get_variable(size_t i) const override { int currentVar = 0;
#define ASMITH_END_REFLECTION_VARIABLES throw std::runtime_error("asmith::reflection_variable::get_function : Index out of bounds"); }
}

#endif