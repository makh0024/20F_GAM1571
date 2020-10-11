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

		//vec2 operator=(vec2& o);

		/*vec2 operator+(const vec2& rhs);
		vec2 operator-(const vec2& rhs);
		vec2 operator*(float o) const;
		vec2 operator/(float o) const;
		vec2 operator+=(const vec2& rhs);
		vec2 operator-=(const vec2& rhs);
		vec2 operator*=(float o);
		vec2 operator/=(float o);
		vec2 operator+(float o) const;*/

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
}