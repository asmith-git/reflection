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

#include "asmith/reflection/master.hpp"

namespace asmith {
	struct reflection_startup {
		reflection_startup() {
			reflection_class::register_class(reflect<void>());
			reflection_class::register_class(reflect<bool>());
			reflection_class::register_class(reflect<char>());
			reflection_class::register_class(reflect<uint8_t>());
			reflection_class::register_class(reflect<uint16_t>());
			reflection_class::register_class(reflect<uint32_t>());
			reflection_class::register_class(reflect<uint64_t>());
			reflection_class::register_class(reflect<int8_t>());
			reflection_class::register_class(reflect<int16_t>());
			reflection_class::register_class(reflect<int32_t>());
			reflection_class::register_class(reflect<int64_t>());
			reflection_class::register_class(reflect<float>());
			reflection_class::register_class(reflect<double>());
		}
	};

	reflection_startup REFLECTION_STARTUP;
}