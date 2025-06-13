#ifndef ROTEX_VEC_H
#define ROTEX_VEC_H

#include <cmath>

#define RTVEC2FZERO RTVec2<float>(0.f, 0.f)
#define RTVEC2IZERO RTVec2<int>(0, 0)
#define RTVEC3FZERO RTVec3<float>(0.f, 0.f, 0.f)
#define RTVEC3IZERO RTVec3<int>(0, 0, 0)
#define RTVEC4FZERO RTVec4<float>(0.f, 0.f, 0.f, 0.f)
#define RTVEC4IZERO RTVec4<int>(0, 0, 0, 0)

template<typename T>
class RTVec2
{
public:
	T x, y;
	double magnitude; // length

	RTVec2(T x, T y)
	{
		this->x = x;
		this->y = y;

		magnitude = std::sqrt((x*x)+(y*y));
	}

	double dot(const RTVec2& b)
	{
		return (x * b.x) + (y * b.y);
	}

	const RTVec2& normalize()
	{
		if (magnitude == 0)
			return nullptr;

		return RTVec2(x / magnitude, y / magnitude);
	}

	inline bool operator==(const RTVec2<T>& b) const
	{
		return (x == b.x && y == b.y);
	}

	inline RTVec2<T> operator-(T scalar) const {
		return RTVec2<T>(x - scalar, y - scalar);
	}
};

template<typename T>
class RTVec3
{
public:
	T x, y, z;
	double magnitude;

	RTVec3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		magnitude = std::sqrt((x * x) + (y * y) + (z * z));
	}

	double dot(const RTVec3& b)
	{
		return (x * b.x) + (y * b.y) + (z * b.z);
	}

	const RTVec3& normalize()
	{
		if (magnitude == 0)
			return nullptr;

		return RTVec3(x / magnitude, y / magnitude, z / magnitude);
	}
};

template<typename T>
class RTVec4
{
public:
	T x, y, z, w;
	double magnitude;

	RTVec4(T x, T y, T z, T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		magnitude = std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	double dot(const RTVec4& b)
	{
		return (x * b.x) + (y * b.y) + (z * b.z) + (w * b.w);
	}

	const RTVec4& normalize()
	{
		if (magnitude == nullptr)
			return nullptr;

		return RTVec4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
	}
};

#endif // ROTEX_VEC_H