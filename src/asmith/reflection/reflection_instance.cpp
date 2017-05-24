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

#include "asmith/reflection/reflection_instance.hpp"

namespace asmith {
	// reflection_instance

	reflection_instance::reflection_instance() :
		mClass(nullptr),
		mData(nullptr)
	{}

	reflection_instance::reflection_instance(const reflection_instance& aOther) :
		mClass(aOther.mClass),
		mData(nullptr)
	{
		if(aOther.mData) {
			mData = operator new(mClass->get_size());
			mClass->get_copy_constructor().call_unsafe(mData, aOther.mData);
		}
	}

	reflection_instance::reflection_instance(reflection_instance&& aOther) :
		mClass(aOther.mClass),
		mData(aOther.mData)
	{
		aOther.mClass = nullptr;
		aOther.mData = nullptr;
	}

	reflection_instance::~reflection_instance() {
		if(mData) {
			mClass->get_destructor().call(mData);
			operator delete(mData);
			mClass = nullptr;
			mData = nullptr;
		}
	}

	const reflection_class& reflection_instance::get_class() const {
		return *mClass;
	}

	reflection_instance reflection_instance::call_unsafe(const char* aName, void* aParams) {
		const reflection_function& fun = mClass->get_function(aName);
		reflection_instance obj(fun.get_return());
		fun.call_unsafe(mData, obj.mData, aParams);
		return obj;
	}

	void* reflection_instance::as_unsafe() {
		return mData;
	}

	const void* reflection_instance::as_unsafe() const {
		return mData;
	}
}