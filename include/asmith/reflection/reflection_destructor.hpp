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

#ifndef ASMITH_REFLECTION_DESTRUCTOR_HPP
#define ASMITH_REFLECTION_DESTRUCTOR_HPP

namespace asmith {
	
	class reflection_class;
	
	class reflection_destructor {
	public:
		virtual ~reflection_destructor() {}
		
		virtual size_t get_modifiers() const = 0;
		virtual void call(void*) const = 0;
	};

	template<class CLASS>
	class auto_reflection_destructor : public reflection_destructor {
	private:
		const size_t mModifiers;
	public:
		auto_reflection_destructor(size_t aModifiers) : 
			mModifiers(aModifiers)
		{}

		// Inherited from reflection_destructor

		size_t get_modifiers() const override {
			return mModifiers;
		}

		void call(void* aObject) const override {
			reinterpret_cast<CLASS*>(aObject)->~CLASS();
		}
	};
}

#endif