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

#ifndef ASMITH_REFLECTION_MODIFIER_HPP
#define ASMITH_REFLECTION_MODIFIER_HPP

namespace asmith {
	enum reflection_modifier {
		REFLECTION_PRIVATE		= 1 << 1,
		REFLECTION_PROTECTED	= 1 << 2,
		REFLECTION_PUBLIC		= 1 << 3,
		REFLECTION_VIRTUAL		= 1 << 4,
		REFLECTION_CONST		= 1 << 5,
		REFLECTION_CONSTEXPR	= 1 << 6,
		REFLECTION_STATIC		= 1 << 7
	};
}

#endif