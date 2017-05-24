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

		virtual void call_unsafe(void*, void*) const = 0;

		void call(void* aObject) const {
			call_unsafe(aObject, nullptr);
		}

		template<class P1>
		void call(void* aObject, reflection_parameter_map<P1> p1) const {
			call_unsafe(&aObject, &p1);
		}

		template<class P1, class P2>
		void call(void* aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3>
		void call(void* aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3, class P4>
		void call(void* aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4) const {
			call_unsafe(aObject, &p1);
		}

		template<class P1, class P2, class P3, class P4, class P5>
		void call(void* aObject, reflection_parameter_map<P1> p1, reflection_parameter_map<P2> p2, reflection_parameter_map<P3> p3, reflection_parameter_map<P4> p4, reflection_parameter_map<P5> p5) const {
			call_unsafe(&aObject, &p1);
		}
	};

		template<class CLASS, class... PARAMS>
	class auto_reflection_constructor : public reflection_constructor {
	private:
		const size_t mModifiers;

		template<class T>
		void call__(void* aObject, void* aParams) const {
			new(aObject) T();
		}

		template<class T, class P1 >
		void call__(void* aObject, void* aParams) const {
			P1 p1 = asmith::get_parameter<P1>(aParams);
			new(aObject) T(p1);
		}

		template<class T, class P1, class P2>
		void call__(void* aObject, void* aParams) const {
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			new(aObject) T(p1, p2);
		}

		template<class T, class P1, class P2, class P3>
		void call__(void* aObject, void* aParams) const {
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			new(aObject) T(p1, p2, p3);
		}

		template<class T, class P1, class P2, class P3, class P4>
		void call__(void* aObject, void* aParams) const {
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			new(aObject) T(p1, p2, p3, p4);
		}

		template<class T, class P1, class P2, class P3, class P4, class P5>
		void call__(void* aObject, void* aParams) const {
			P1 p1 = asmith::get_parameter<P1>(aParams);
			P2 p2 = asmith::get_parameter<P2>(aParams);
			P3 p3 = asmith::get_parameter<P3>(aParams);
			P4 p4 = asmith::get_parameter<P4>(aParams);
			P5 p5 = asmith::get_parameter<P5>(aParams);
			new(aObject) T(p1, p2, p3, p4, p5);
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
			return reflect_type_at<PARAMS...>(aIndex);
		}

		size_t get_modifiers() const override {
			return mModifiers;
		}

		void call_unsafe(void* aObject, void* aParams) const override {
			call__<CLASS, PARAMS...>(aObject, aParams);
		}
	};
}

#endif