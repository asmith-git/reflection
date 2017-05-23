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

		virtual void call_unsafe(void*, const void*) const = 0;

		void call(void* aObject) const {
			call_unsafe(aObject, nullptr);
		}

		template<class P1>
		void call(void* aObject, P1 p1) const {
			call_unsafe(&aObject, &p1);
		}

		template<class P1, class P2>
		void call(void* aObject, P1 p1, P2 p2) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3>
		void call(void* aObject, P1 p1, P2 p2, P3 p3) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3, class P4>
		void call(void* aObject, P1 p1, P2 p2, P3 p3, P4 p4) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3, class P4, class P5>
		void call(void* aObject, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {
			call_unsafe(&aObject, &p1);
		}
	};

		template<class CLASS, class... PARAMS>
	class auto_reflection_constructor : public reflection_constructor {
	private:
		const size_t mModifiers;

		template<class T>
		void call__(void* aObject, const void* aParams) const {
			new(aObject) T();
		}

		template<class T, class P1 >
		void call__(void* aObject, const void* aParams) const {
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			new(aObject) T(*p1);
		}

		template<class T, class P1, class P2>
		void call__(void* aObject, const void* aParams) const {
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			new(aObject) T(*p1, *p2);
		}

		template<class T, class P1, class P2, class P3>
		void call__(void* aObject, const void* aParams) const {
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			new(aObject) T(*p1, *p2, *p3);
		}

		template<class T, class P1, class P2, class P3, class P4>
		void call__(void* aObject, const void* aParams) const {
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			new(aObject) T(*p1, *p2, *p3, *p4);
		}

		template<class T, class P1, class P2, class P3, class P4, class P5>
		void call__(void* aObject, const void* aParams) const {
			const P1* const p1 = reinterpret_cast<const P1*>(aParams);
			const P2* const p2 = reinterpret_cast<const P2*>(reinterpret_cast<const uint8_t*>(p1) + sizeof(P1));
			const P3* const p3 = reinterpret_cast<const P3*>(reinterpret_cast<const uint8_t*>(p2) + sizeof(P2));
			const P4* const p3 = reinterpret_cast<const P4*>(reinterpret_cast<const uint8_t*>(p3) + sizeof(P3));
			const P5* const p3 = reinterpret_cast<const P5*>(reinterpret_cast<const uint8_t*>(p4) + sizeof(P4));
			new(aObject) T(*p1, *p2, *p3, *p4, *p5);
		}
	public:
		auto_reflection_constructor(const size_t aModifiers) :
			mModifiers(aModifiers)
		{}

		// Inherited from reflection_constructor

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
			default: throw std::runtime_error("asmith::reflection_constructor::get_parameter : Index out of bounds");
			}
		}

		size_t get_modifiers() const override {
			return mModifiers;
		}

		void call_unsafe(void* aObject, const void* aParams) const override {
			call__<CLASS, PARAMS...>(aObject, aParams);
		}
	};
}

#endif