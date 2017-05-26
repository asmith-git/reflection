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

#ifndef ASMITH_REFLECTION_PRIMATIVES_HPP
#define ASMITH_REFLECTION_PRIMATIVES_HPP

#include "reflection_class.hpp"
#include "reflection_constructor.hpp"
#include "reflection_destructor.hpp"

namespace asmith {


#define ASMITH_REFLECTION_PRIMATIVE_REFLECT(aName)\
	template<>\
	struct asmith::reflection_specialisation<aName> {\
		static inline const asmith::reflection_class& reflect() throw() {\
			static const asmith::auto_reflection_class<aName> REFLECTION = auto_reflection_class<aName>(#aName)\
				.constructor(asmith::REFLECTION_PUBLIC)\
				.constructor<aName>(asmith::REFLECTION_PUBLIC)\
				.destructor(asmith::REFLECTION_PUBLIC);\
			return REFLECTION;\
		}\
	};

#define ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(aName, aAlias)\
	template<>\
	struct asmith::reflection_specialisation<aName> {\
		static inline const asmith::reflection_class& reflect() throw() {\
			static const asmith::auto_reflection_class<aName> REFLECTION = auto_reflection_class<aName>(#aName)\
				.constructor(asmith::REFLECTION_PUBLIC)\
				.constructor<aName>(asmith::REFLECTION_PUBLIC)\
				.destructor(asmith::REFLECTION_PUBLIC)\
				.alias(#aAlias);\
			return REFLECTION;\
		}\
	};

#define ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS_2(aName, aAlias1, aAlias2)\
	template<>\
	struct asmith::reflection_specialisation<aName> {\
		static inline const asmith::reflection_class& reflect() throw() {\
			static const asmith::auto_reflection_class<aName> REFLECTION = auto_reflection_class<aName>(#aName)\
				.constructor(asmith::REFLECTION_PUBLIC)\
				.constructor<aName>(asmith::REFLECTION_PUBLIC)\
				.destructor(asmith::REFLECTION_PUBLIC)\
				.alias(#aAlias1)\
				.alias(#aAlias2);\
			return REFLECTION;\
		}\
	};

	ASMITH_REFLECTION_PRIMATIVE_REFLECT(bool)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(char)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(uint8_t, unsigned char)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(uint16_t, unsigned short)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(uint32_t, unsigned int)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(uint64_t, unsigned long)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS(int8_t, signed char)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS_2(int16_t, signed short, short)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS_2(int32_t, signed int, int)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT_WITH_ALIAS_2(int64_t, signed long, long)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(float)
	ASMITH_REFLECTION_PRIMATIVE_REFLECT(double)
}

#endif