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

#ifndef ASMITH_REFLECTION_CONSTRUCTOR_HPP
#define ASMITH_REFLECTION_CONSTRUCTOR_HPP

namespace asmith {
	
	class reflection_class;
	
	class reflection_constructor {
	public:
		virtual ~reflection_constructor() {}
		
		virtual size_t get_parameter_count() const = 0;
		virtual const reflection_class& get_parameter(size_t) const = 0;
		virtual size_t get_modifiers() const = 0;
		virtual void call(void*, const void*) const = 0;
	};	
	
	template<class CLASS, uint32_t MODS, class ...PARAMS>
	class auto_reflection_constructor : public reflection_constructor {
	private:
		template<class A>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			new(aObject) CLASS(*a);
		}

		template<class A, class B>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
			new(aObject) CLASS(*a, *b);
		}

		template<class A, class B, class C>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
			const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
			new(aObject) CLASS(*a, *b, *c);
		}

		template<class A, class B, class C, class D>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
			const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
			const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
			new(aObject) CLASS(*a, *b, *c, *d);
		}

		template<class A, class B, class C, class D, class E>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
			const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
			const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
			const E* e = reinterpret_cast<const E*>(reinterpret_cast<const uint8_t*>(d) + sizeof(D));
			new(aObject) CLASS(*a, *b, *c, *d, *e);
		}

		template<class A, class B, class C, class D, class E, class F>
		void call__(void* aObject, const void* aParams) const {
			const A* a = reinterpret_cast<const A*>(reinterpret_cast<const uint8_t*>(aParams) + 0);
			const B* b = reinterpret_cast<const B*>(reinterpret_cast<const uint8_t*>(a) + sizeof(A));
			const C* c = reinterpret_cast<const C*>(reinterpret_cast<const uint8_t*>(b) + sizeof(B));
			const D* d = reinterpret_cast<const D*>(reinterpret_cast<const uint8_t*>(c) + sizeof(C));
			const E* e = reinterpret_cast<const E*>(reinterpret_cast<const uint8_t*>(d) + sizeof(D));
			const F* f = reinterpret_cast<const F*>(reinterpret_cast<const uint8_t*>(e) + sizeof(E));
			new(aObject) CLASS(*a, *b, *c, *d, *e, *f);
		}

		template<class... P>
		typename std::enable_if<sizeof...(P) == 0, void>::type call_(void* aObject, const void* aParams) const {
			new(aObject) CLASS();
		}

		template<class... P>
		typename std::enable_if<sizeof...(P) != 0, void>::type call_(void* aObject, const void* aParams) const {
			call__<P...>(aObject, aParams);
		}

		template<size_t I, class...P>
		static constexpr bool get_parameter_condition() {
			return I < sizeof...(P);
		}

	public:
		// Inherited from reflection_constructor
		size_t get_parameter_count() const override {
			return sizeof...(PARAMS); 
		}
			
		const asmith::reflection_class& get_parameter(size_t i) const override { 
			switch (i) {
				case 0: return get_reflection_class<typename type_at_index<0, PARAMS...>>();
				case 1: return get_reflection_class<typename type_at_index<1, PARAMS...>>();
				case 2: return get_reflection_class<typename type_at_index<2, PARAMS...>>();
				case 3: return get_reflection_class<typename type_at_index<3, PARAMS...>>();
				case 4: return get_reflection_class<typename type_at_index<4, PARAMS...>>();
				case 5: return get_reflection_class<typename type_at_index<5, PARAMS...>>();
				default : throw std::runtime_error("asmith::reflection_constructor_implementation::get_parameter : Not yet implemented");
			}
		}

		size_t get_modifiers() const override {
			return MODS;
		}

		void call(void* aObject, const void* aParams) const override {
			call_<PARAMS...>(aObject, aParams);
		}
	};
}

#endif