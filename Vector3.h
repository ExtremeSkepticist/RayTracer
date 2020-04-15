#pragma once

#include <cstdlib>
#include <iostream>

template<typename T>
class Vector3 final
{
public:
	Vector3();
	Vector3(T x);
	Vector3(T x, T y, T z);
	Vector3(const Vector3<T>& other) = default;
	Vector3(Vector3<T>&& other) = default;
	virtual ~Vector3() = default;

	Vector3<T> operator+(const Vector3& other) const;
	Vector3<T> operator-(const Vector3& other) const;
	Vector3<T> operator-() const;
	Vector3<T> operator*(const T& value) const;
	Vector3<T> operator*(const Vector3& other) const;
	Vector3<T>& operator=(const Vector3& other) = default;
	Vector3<T>& operator=(Vector3&& other) = default;
	Vector3<T>& operator+=(const Vector3& other);
	Vector3<T>& operator*=(const Vector3& other);
	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector);

	T GetDotProduct(const Vector3<T>& other) const;
	T GetLength() const;
	T GetSop() const;
	T GetX() const;
	T GetY() const;
	T GetZ() const;
	void SetX(const T& x);
	void SetY(const T& y);
	void SetZ(const T& z);
	Vector3<T>& Normalize();

private:
	T mX;
	T mY;
	T mZ;
};

template<typename T>
Vector3<T>::Vector3()
	: mX(0)
	, mY(0)
	, mZ(0)
{
}

template<typename T>
Vector3<T>::Vector3(T x)
	: mX(x)
	, mY(x)
	, mZ(x)
{
}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z)
	: mX(x)
	, mY(y)
	, mZ(z)
{
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& other) const
{
	return Vector3<T>(mX + other.mX, mY + other.mY, mZ + other.mZ);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3& other) const
{
	return Vector3<T>(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

template<typename T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3<T>(-mX, -mY, -mZ);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const T& value) const
{
	return Vector3<T>(mX * value, mY * value, mZ * value);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3& other) const
{
	return Vector3<T>(mX * other.mX, mY * other.mY, mZ * other.mZ);
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& other)
{
	mX += other.mX;
	mY += other.mY;
	mZ += other.mZ;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(const Vector3& other)
{
	mX *= other.mX;
	mY *= other.mY;
	mZ *= other.mZ;

	return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector)
{
	os << "(" << vector.mX << ", " << vector.mY << ", " << vector.mZ << ")";
	return os;
}

template<typename T>
T Vector3<T>::GetDotProduct(const Vector3<T>& other) const
{
	return mX * other.mX + mY * other.mY + mZ * other.mZ;
}

template<typename T>
T Vector3<T>::GetLength() const
{
	return sqrt(GetSop());
}

template<typename T>
T Vector3<T>::GetSop() const
{
	return mX * mX + mY * mY + mZ * mZ;
}

template<typename T>
T Vector3<T>::GetX() const
{
	return mX;
}

template<typename T>
T Vector3<T>::GetY() const
{
	return mY;
}

template<typename T>
T Vector3<T>::GetZ() const
{
	return mZ;
}

template<typename T>
void Vector3<T>::SetX(const T& x)
{
	mX = x;
}

template<typename T>
void Vector3<T>::SetY(const T& y)
{
	mY = y;
}

template<typename T>
void Vector3<T>::SetZ(const T& z)
{
	mZ = z;
}

template<typename T>
Vector3<T>& Vector3<T>::Normalize()
{
	T nor = GetSop();
	if (nor > 0)
	{
		T invNor = 1 / sqrt(nor);

		mX *= invNor;
		mY *= invNor;
		mZ *= invNor;
	}

	return *this;
}