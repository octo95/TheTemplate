#pragma once
#include "template.h"
#include <functional>

template<>
class std::hash<Tmpl8::vec2>
{
public:
	size_t operator()(const Tmpl8::vec2& key) const
	{
		size_t h1 = std::hash<float>{}(key.x);
		size_t h2 = std::hash<float>{}(key.y);
		return h1 ^ (h2 << 1);
	}
};
