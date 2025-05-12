#pragma once
#include "template.h"
#include <functional>

// Hash the vec2 type from the template, based on the logic from https://en.cppreference.com/w/cpp/utility/hash.

template<>
class std::hash<Tmpl8::vec2>
{
public:
	// Overload the function call operator to work with a vec2 key.
	size_t operator()(const Tmpl8::vec2& key) const
	{
		// Hash the x and y elements of vec2(x,y).
		size_t h1 = std::hash<float>{}(key.x);
		size_t h2 = std::hash<float>{}(key.y);

		// Bitwise combination
		return h1 ^ (h2 << 1);
	}
};
