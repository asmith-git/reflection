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
#define ASMITH_REFLECTION_DESTRUCTOR(aMods)\
	const asmith::reflection_destructor& get_destructor() const override { \
		class destructor : public reflection_destructor {\
		public:\
			size_t get_modifiers() const override { return aMods; }\
			void call(void* aObject) const override { static_cast<ASMITH_REFLECTION_CLASS_NAME*>(aObject)->~ASMITH_REFLECTION_CLASS_NAME(); }\
		};\
		static destructor DESTRUCTOR;\
		return DESTRUCTOR;\
	}

#define ASMITH_BEGIN_REFLECTION_CONSTRUCTORS const asmith::reflection_constructor& get_constructor(size_t i) const override { int currentConstructor = 0;
#define ASMITH_END_REFLECTION_CONSTRUCTORS throw std::runtime_error("asmith::reflection_variable::get_constructor : Index out of bounds"); }

	namespace implementation {
		template<class C, uint32_t MODS, class ...PARAMS>
		class reflection_constructor_implementation : public reflection_constructor {
		private:
			template<class A>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				new(aObject) C(*a);
			}

			template<class A, class B>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
				new(aObject) C(*a, *b);
			}

			template<class A, class B, class C>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
				const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
				new(aObject) C(*a, *b, *c);
			}

			template<class A, class B, class C, class D>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
				const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
				const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
				new(aObject) C(*a, *b, *c, *d);
			}

			template<class A, class B, class C, class D, class E>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
				const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
				const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
				const E* e = reinterpret_cast<const E*>(reinterpret_cast<const uint8_t*>(d) + sizeof(D));
				new(aObject) C(*a, *b, *c, *d, *e);
			}

			template<class A, class B, class C, class D, class E, class F>
			void call__(void* aObject, const void* aParams) const {
				const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
				const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
				const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
				const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
				const E* e = reinterpret_cast<const E*>(reinterpret_cast<const uint8_t*>(d) + sizeof(D));
				const F* f = reinterpret_cast<const F*>(reinterpret_cast<const uint8_t*>(e) + sizeof(E));
				new(aObject) C(*a, *b, *c, *d, *e, *f);
			}

			template<class... P>
			typename std::enable_if<sizeof...(P) == 0, void>::type call_(void* aObject, const void* aParams) const {
				new(aObject) C();
			}

			template<class... P>
			typename std::enable_if<sizeof...(P) != 0, void>::type call_(void* aObject, const void* aParams) const {
				call__<P...>(aObject, aParams);
			}
		public:
			// Inherited from reflection_constructor
			size_t get_parameter_count() const override {
				return sizeof...(PARAMS); 
			}
			
			const asmith::reflection_class& get_parameter(size_t i) const override { 
				//! \todo Implement
				throw std::runtime_error("asmith::reflection_constructor_implementation::get_parameter : Not yet implemented"); 
			}

			size_t get_modifiers() const override {
				return MODS;
			}

			void call(void* aObject, const void* aParams) const override {
				call_<PARAMS...>(aObject, aParams);
			}
		};
	}

#define ASMITH_REFLECTION_TRIVIAL_CONSTRUCTOR(aMods) \
	if(i == currentConstructor) {\
		static implementation::reflection_constructor_implementation<ASMITH_REFLECTION_CLASS_NAME, aMods> constructor; \
		return constructor; \
	}\
	++currentConstructor;

#define ASMITH_REFLECTION_CONSTRUCTOR(aMods, aParams) \
	if(i == currentConstructor) {\
		static implementation::reflection_constructor_implementation<ASMITH_REFLECTION_CLASS_NAME, aMods, aParams> constructor; \
		return constructor; \
	}\
	++currentConstructor;

#define ASMITH_REFLECTION_COPY_CONSTRUCTOR(aMods) ASMITH_REFLECTION_CONSTRUCTOR(aMods, ASMITH_REFLECTION_CLASS_NAME)

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
			const reflection_class& get_parent_class(size_t) const override { throw 0; }

			ASMITH_REFLECTION_DESTRUCTOR(REFLECTION_PUBLIC)

			ASMITH_BEGIN_REFLECTION_CONSTRUCTORS
				ASMITH_REFLECTION_TRIVIAL_CONSTRUCTOR(REFLECTION_PUBLIC)
				ASMITH_REFLECTION_COPY_CONSTRUCTOR(REFLECTION_PUBLIC)
			ASMITH_END_REFLECTION_CONSTRUCTORS

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