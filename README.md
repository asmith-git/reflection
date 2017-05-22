## Features
2. Creation and destruction of objects
3. Calling functions
4. Setting and getting variables

## Todo
1. Further testing
2. Support for pointers and references
3. Support for templated classes
4. Support for constructors on abstract classes

## Example
```C++
using namespace asmith;

// This is the class we want to reflect
class objective_function {
private:
	int mDimensions;
	float mLowerBound;
	float mUpperBound;
public:
	objective_function() {}
	objective_function(int d, float l, float u) : mDimensions(d), mLowerBound(l), mUpperBound(u) {}

	virtual ~objective_function() {}

	int get_dimensions() const { return mDimensions; }
	float get_lower_bound() const { return mLowerBound; }
	float get_upper_bound() const { return mUpperBound; }
	virtual float run(float*) const { return 0.f; }

  // This function defines which parts of the class are reflected
	static reflection_class& get_reflection() {
		static auto_reflection_class<objective_function> REFLECTION =
			auto_reflection_class<objective_function>("objective_function")
			.constructor(REFLECTION_PUBLIC)
			.constructor<int, float, float>(REFLECTION_PUBLIC)
			.destructor(REFLECTION_PUBLIC | REFLECTION_VIRTUAL)
			.function<float>("get_lower_bound", &objective_function::get_lower_bound, REFLECTION_PUBLIC | REFLECTION_CONST)
			.function<float>("get_upper_bound", &objective_function::get_upper_bound, REFLECTION_PUBLIC | REFLECTION_CONST)
			.function<float, float*>("run", &objective_function::run, REFLECTION_PUBLIC | REFLECTION_CONST | REFLECTION_VIRTUAL)
			.variable<int>("mDimensions", &objective_function::mDimensions, REFLECTION_PRIVATE)
			.variable<float>("mLowerBound", &objective_function::mLowerBound, REFLECTION_PRIVATE)
			.variable<float>("mUpperBound", &objective_function::mUpperBound, REFLECTION_PRIVATE);
		return REFLECTION;
	}
};

// This specialisation tells the reflection library which reflection_class to use when the type is used as a variable, fuction return or parameter
namespace asmith {
	template<>
	struct reflection_specialisation<objective_function> {
		static inline const reflection_class& reflect() {
			return objective_function::get_reflection();
		}
	};
}
```
