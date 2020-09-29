#pragma once

namespace fw
{
	class vec2
	{
	public:
		vec2(float ax, float ay);
		~vec2();

		float x;
		float y;
	};

	class vec3
	{
	public:
		vec3(float x, float y, float z);

		float x;
		float y;
		float z;
	};
}