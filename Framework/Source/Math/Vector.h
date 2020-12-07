#pragma once

#include <cmath>

namespace fw
{
	class vec2
	{
	public:
		vec2();
		vec2(float ax, float ay);
		~vec2();

		float x;
		float y;

		vec2 operator+(float o) const { return vec2(x + o, y + o); }
		vec2 operator-(float o) const { return vec2(x - o, y - o); }
		vec2 operator*(float o) const { return vec2(x * o, y * o); }
		vec2 operator/(float o) const { return vec2(x / o, y / o); }

		vec2 operator-=(const float o) { return vec2(x -= o, y -= o); }
		vec2 operator*=(const float o) { return vec2(x *= o, y *= o); }
		vec2 operator/=(const float o) { return vec2(x /= o, y /= o); }
		vec2 operator+=(const float o) { return vec2(x += o, y += o); }

		vec2 operator+(vec2 o) const { return vec2(x + o.x, y + o.y); }
		vec2 operator-(vec2 o) const { return vec2(x - o.x, y - o.y); }
		vec2 operator*(vec2 o) const { return vec2(x * o.x, y * o.y); }
		vec2 operator/(vec2 o) const { return vec2(x / o.x, y / o.y); }

		vec2 operator+=(const vec2& o) { return vec2(x += o.x, y += o.y); }
		vec2 operator-=(const vec2& o) { return vec2(x -= o.x, y -= o.y); }
		vec2 operator*=(const vec2& o) { return vec2(x *= o.x, y *= o.y); }
		vec2 operator/=(const vec2& o) { return vec2(x /= o.x, y /= o.y); }

		bool operator==(vec2 o);
		bool operator!=(vec2 o);

		bool operator>(vec2 o);
		bool operator<(vec2 o);
		bool operator>=(vec2 o);
		bool operator<=(vec2 o);

		bool isInRange(vec2 o);

		float Magnitude();
		float Distance(vec2 o);
		void Normalize();

		vec2 Normalized();

		float DotProduct(vec2 o);

		void SetValues(float o, float o2);


	};

	class vec3
	{
	public:
		vec3(float x, float y, float z);

		float x;
		float y;
		float z;
	};

	class vec4
	{
	public:
		vec4(float ax, float ay, float az, float aw);

		float x;
		float y;
		float z;
		float w;

		static const vec4 Red(float alpha)			{ return vec4(1, 0, 0, alpha);	}
		static const vec4 Green(float alpha)		{ return vec4(0, 1, 0, alpha); }
		static const vec4 Blue(float alpha)			{ return vec4(0, 0, 1, alpha); }
		static const vec4 White(float alpha)		{ return vec4(0.7f, 0.7f, 0.7f, alpha); }
		static const vec4 Black(float alpha)		{ return vec4(0, 0, 0, alpha); }
		static const vec4 LightOrange(float alpha)	{ return vec4(0.96f, 0.556f, 0.366f, alpha); }
	};

	class ivec2
	{
	public:
		ivec2() { x = 0, y = 0; }
		ivec2(int ax, int ay) {  x = ax, y = ay; }

		void Set(int nx, int ny) { x = nx; y = ny; }

	public:
		int x, y;
	};
}