// Massgate
// Copyright (C) 2017 Ubisoft Entertainment
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#pragma once 
//template based vector classes

//NOTE: Default constructors DO NOT initialize members (this is a speed optimization)

//FORWARD DECLARATIONS
template <class Type> class Core_Vector3;
template <class Type> class Core_Vector4;


//2D VECTOR
template <class Type>
class Core_Vector2
{
public:

	//CONSTRUCTORS
	Core_Vector2() {}
	Core_Vector2(Type aX, Type aZ) { myX = aX; myZ = aZ; }
	Core_Vector2(const Core_Vector3<Type>& aCore_Vector) { myX = aCore_Vector.myX; myZ = aCore_Vector.myZ; }

	template <class AnotherType>
	Core_Vector2(const Core_Vector2<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myZ = (Type)aCore_Vector.myZ; }

	//DESTRUCTOR
	~Core_Vector2() {}

	//ASSIGNMENT
	void Set(Type aX, Type aZ) { myX = aX; myZ = aZ; }
	template <class AnotherType>
	Core_Vector2<Type>& operator=(const Core_Vector2<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myZ = (Type)aCore_Vector.myZ; return *this; }
	Core_Vector2<Type>& operator=(const Core_Vector2<Type>& aCore_Vector) { myX = aCore_Vector.myX; myZ = aCore_Vector.myZ; return *this; }
	Core_Vector2<Type>& operator=(const Core_Vector3<Type>& aCore_Vector) { myX = aCore_Vector.myX; myZ = aCore_Vector.myZ; return *this; }

	//MODIFYING OPERATIONS
	Core_Vector2<Type>& operator+=(const Core_Vector2<Type>& aCore_Vector) { myX += aCore_Vector.myX; myZ += aCore_Vector.myZ; return *this; }
	Core_Vector2<Type>& operator-=(const Core_Vector2<Type>& aCore_Vector) { myX -= aCore_Vector.myX; myZ -= aCore_Vector.myZ; return *this; }

	Core_Vector2<Type>& operator*=(Type aValue) { myX *= aValue; myZ *= aValue; return *this; }
	Core_Vector2<Type>& operator/=(Type aValue) { myX /= aValue; myZ /= aValue; return *this; }

	//CREATIVE OPERATORS WITH VECTORS
	Core_Vector2<Type> operator+(const Core_Vector2<Type>& aCore_Vector) const { return Core_Vector2<Type>(myX + aCore_Vector.myX, myZ + aCore_Vector.myZ); }
	Core_Vector2<Type> operator-(const Core_Vector2<Type>& aCore_Vector) const { return Core_Vector2<Type>(myX - aCore_Vector.myX, myZ - aCore_Vector.myZ); }
	Core_Vector2<Type> operator*(const Core_Vector2<Type>& aCore_Vector) const { return Core_Vector2<Type>(myX * aCore_Vector.myX, myZ * aCore_Vector.myZ); }
	Core_Vector2<Type> operator/(const Core_Vector2<Type>& aCore_Vector) const { return Core_Vector2<Type>(myX / aCore_Vector.myX, myZ / aCore_Vector.myZ); }

	//CREATIVE OPERATORS WITH SCALARS
	Core_Vector2<Type> operator*(Type aValue) const { return Core_Vector2<Type>(myX * aValue, myZ * aValue); }
	Core_Vector2<Type> operator/(Type aValue) const { return Core_Vector2<Type>(myX / aValue, myZ / aValue); }

	//COMPARISON
	int operator==(const Core_Vector2<Type>& aCore_Vector) const { return (myX == aCore_Vector.myX && myZ == aCore_Vector.myZ); }
	int operator!=(const Core_Vector2<Type>& aCore_Vector) const { return !(*this == aCore_Vector); }

	//NEGATION
	Core_Vector2<Type> operator-() const { return Core_Vector2<Type>(-myX, -myZ); }

	//MATH
	Core_Vector2<Type> Normal() const { return Core_Vector2<Type>(myZ, -myX); }
	Type Length() const { return (Type)(sqrt((Type)(myX * myX + myZ * myZ))); }
	Type Length2() const { return (myX * myX + myZ * myZ); }
	Core_Vector2<Type>& Scale(Type aCore_Vector) { Normalize(); operator *= (aCore_Vector); return *this; }
	Core_Vector2<Type>& Normalize() { operator /= (Length()); return *this; }
	Core_Vector2<Type>& NormalizeSafe() { if (Length2() > (Type)0.00001)  Normalize(); else myX = myZ = 0; return *this; }

	Core_Vector2<Type> GetNormalized() const { return *this / Length(); }
	Core_Vector2<Type> GetNormalizedSafe() const { Core_Vector2<Type>(*this).NormalizeSafe(); }

	Core_Vector2<Type>& MulElements(const Core_Vector2<Type>& aVect) { x *= aVect.x; y *= aVect.y; return *this; }

	//UTILITY
	//true if the vector is right of aVect
	bool RightOf(const Core_Vector2<Type>& aVect) const { return ((myX * aVect.myZ) < (myZ * aVect.myX)); }

	//true if the vector is left of aVect
	bool LeftOf(const Core_Vector2<Type>& aVect) const { return ((myX * aVect.myZ) > (myZ * aVect.myX)); }

	//if deviation > 0, the vector is right of aVect
	//if deviation < 0, the vector is left of aVect
	Type Deviation(const Core_Vector2<Type>& aVect) const { return ((myX * aVect.myZ) - (myZ * aVect.myX)); }

	//create aCore_Vector vector rotated 90 degrees right
	Core_Vector2<Type> CreateRightNormal() const { return Core_Vector2<Type>(-myZ, myX); }

	//create aCore_Vector vector rotated 90 degrees left
	Core_Vector2<Type> CreateLeftNormal()	const { return Core_Vector2<Type>(myZ, -myX); }

	//Rotate the vector
	Core_Vector2<Type>& Rotate(float anAngle)
	{
		float sinVal, cosVal;
		Core_SinCos(anAngle, &sinVal, &cosVal);
		Type temp;

		temp = (Type)(myX * cosVal + myY * sinVal);
		myY = (Type)(myY * cosVal - myX * sinVal);
		myX = temp;
		return *this;
	}

	//dot product
	Type Dot(const Core_Vector2<Type>& aCore_Vector) const { return aCore_Vector.myX * myX + aCore_Vector.myZ * myZ; }

	//members
	union { Type myX; Type myU; Type myWidth; Type x; };
	union { Type myZ; Type myY; Type myV; Type myHeight; Type y; Type z; };
};


//3D VECTOR
template <class Type>
class Core_Vector3
{
public:
	//CONSTRUCTORS
	Core_Vector3() {}
	Core_Vector3(Type aX, Type aY, Type aZ) { myX = aX; myY = aY; myZ = aZ; }

	template <class AnotherType>
	Core_Vector3(const Core_Vector2<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = 0; myZ = (Type)aCore_Vector.myZ; }

	template <class AnotherType>
	Core_Vector3(const Core_Vector3<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; }

	template <class AnotherType>
	Core_Vector3(const Core_Vector4<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; }

	//DESTRUCTOR
	~Core_Vector3() {}

	//ASSIGNMENT
	void Set(Type aX, Type aY, Type aZ) { myX = aX; myY = aY; myZ = aZ; }

	template <class AnotherType>
	Core_Vector3<Type>& operator=(const Core_Vector2<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = 0; myZ = (Type)aCore_Vector.myZ; return *this; }

	template <class AnotherType>
	Core_Vector3<Type>& operator=(const Core_Vector3<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; return *this; }

	template <class AnotherType>
	Core_Vector3<Type>& operator=(const Core_Vector4<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; return *this; }

	//MODIFYING OPERATIONS
	Core_Vector3<Type>& operator+=(const Core_Vector3<Type>& aCore_Vector) { myX += aCore_Vector.myX; myY += aCore_Vector.myY; myZ += aCore_Vector.myZ; return *this; }
	Core_Vector3<Type>& operator-=(const Core_Vector3<Type>& aCore_Vector) { myX -= aCore_Vector.myX; myY -= aCore_Vector.myY; myZ -= aCore_Vector.myZ; return *this; }

	Core_Vector3<Type>& operator*=(Type aValue) { myX *= aValue; myY *= aValue; myZ *= aValue; return *this; }
	Core_Vector3<Type>& operator/=(Type aValue) { Type inv = (Type)1.0 / aValue; myX *= inv; myY *= inv; myZ *= inv; return *this; }

	//CREATIVE OPERATORS
	Core_Vector3<Type> operator+(const Core_Vector3<Type>& aCore_Vector) const { return Core_Vector3<Type>(myX + aCore_Vector.myX, myY + aCore_Vector.myY, myZ + aCore_Vector.myZ); }
	Core_Vector3<Type> operator-(const Core_Vector3<Type>& aCore_Vector) const { return Core_Vector3<Type>(myX - aCore_Vector.myX, myY - aCore_Vector.myY, myZ - aCore_Vector.myZ); }

	Core_Vector3<Type>  operator*(Type aValue) const { return Core_Vector3<Type>(myX * aValue, myY * aValue, myZ * aValue); }
	Core_Vector3<Type>  operator/(Type aValue) const { return Core_Vector3<Type>(myX / aValue, myY / aValue, myZ / aValue); }

	//COMPARISON
	bool operator==(const Core_Vector3<Type>& aCore_Vector) const { return (myX == aCore_Vector.myX) && (myY == aCore_Vector.myY) && (myZ == aCore_Vector.myZ); }
	bool operator!=(const Core_Vector3<Type>& aCore_Vector) const { return (myX != aCore_Vector.myX) || (myY != aCore_Vector.myY) || (myZ != aCore_Vector.myZ); }

	//NEGATION
	Core_Vector3<Type> operator-() const { return Core_Vector3<Type>(-myX, -myY, -myZ); }

	//MATH
	Type Length() const { return (Type)(sqrt(myX * myX + myY * myY + myZ * myZ)); }
	Type Length2() const { return (myX * myX + myY * myY + myZ * myZ); }
	Type Length2D() const { return (Type)(sqrt(myX * myX + myZ * myZ)); }
	Type Length2D2() const { return (myX * myX + myZ * myZ); }
	Core_Vector3<Type>& Scale(Type aValue) { Normalize(); operator *= (aValue); return *this; }

	Core_Vector3<Type>& Normalize() { operator /= (Length()); return *this; }
	Core_Vector3<Type>& NormalizeSafe();

	Core_Vector3<Type> GetNormalized() const { return *this / Length(); }
	Core_Vector3<Type> GetNormalizedSafe() const;

	Core_Vector3<Type>& NormalizeFast();
	Core_Vector3<Type>& NormalizeFastSafe();

	Core_Vector3<Type>& MulElements(const Core_Vector3<Type>& aCore_Vector) { x *= aCore_Vector.x; y *= aCore_Vector.y; z *= aCore_Vector.z; return *this; }
	Core_Vector3<Type> Unit() const { return Core_Vector3<Type>(*this).Normalize(); }
	Core_Vector3<Type> UnitSafe() const { return Core_Vector3<Type>(*this).NormalizeSafe(); }

	Type Psi() const { return atan2(myX, myZ); }
	Type Theta() const { return atan2(myY, sqrt(myX * myX + myZ * myZ)); }

	Core_Vector3<Type> GetMin(const Core_Vector3<Type>& aCore_Vector) const
	{
		return Core_Vector3<Type>(__min(x, aCore_Vector.x), __min(y, aCore_Vector.y), __min(z, aCore_Vector.z));
	}

	Core_Vector3<Type> GetMax(const Core_Vector3<Type>& aCore_Vector) const
	{
		return Core_Vector3<Type>(__max(x, aCore_Vector.x), __max(y, aCore_Vector.y), __max(z, aCore_Vector.z));
	}

	Core_Vector3<Type> Cross(const Core_Vector3<Type>& aCore_Vector) const
	{
		return Core_Vector3<Type>(
			myY * aCore_Vector.myZ - myZ * aCore_Vector.myY,
			myZ * aCore_Vector.myX - myX * aCore_Vector.myZ,
			myX * aCore_Vector.myY - myY * aCore_Vector.myX);
	}

	Type Dot(const Core_Vector3<Type>& aCore_Vector) const { return aCore_Vector.myX * myX + aCore_Vector.myY * myY + aCore_Vector.myZ * myZ; }

	//Rotate the vector around x
	Core_Vector3<Type>& RotateAroundX(float anAngle)
	{
		float sinVal, cosVal;
		Core_SinCos(anAngle, &sinVal, &cosVal);
		Type temp;

		temp = (Type)(myY * cosVal + myZ * sinVal);
		myZ = (Type)(myZ * cosVal - myY * sinVal);
		myY = temp;
		return *this;
	}

	//Rotate the vector around y
	Core_Vector3<Type>& RotateAroundY(float anAngle)
	{
		float sinVal, cosVal;
		Core_SinCos(anAngle, &sinVal, &cosVal);
		Type temp;

		temp = (Type)(myX * cosVal + myZ * sinVal);
		myZ = (Type)(myZ * cosVal - myX * sinVal);
		myX = temp;
		return *this;
	}

	//Rotate the vector around z
	Core_Vector3<Type>& RotateAroundZ(float anAngle)
	{
		float sinVal, cosVal;
		Core_SinCos(anAngle, &sinVal, &cosVal);
		Type temp;

		temp = (Type)(myX * cosVal + myY * sinVal);
		myY = (Type)(myY * cosVal - myX * sinVal);
		myX = temp;
		return *this;
	}

	// ACCESS
	__forceinline const Type operator[](int index) const { return (&x)[index]; }
	__forceinline Type& operator[](int index) { return (&x)[index]; }

	//MEMBERS
	union { Type myX; Type myR; Type x; Type r; };
	union { Type myY; Type myG; Type y; Type g; };
	union { Type myZ; Type myB; Type z; Type b; };
};



//4d vector
template <class Type>
class Core_Vector4
{
public:
	//CONSTRUCTORS
	Core_Vector4() {}
	Core_Vector4(Type aX, Type aY, Type aZ, Type aW = Type(1)) { myX = aX; myY = aY; myZ = aZ; myW = aW; }

	template <class AnotherType>
	Core_Vector4(const Core_Vector4<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; myW = (Type)aCore_Vector.myW; }

	template <class AnotherType>
	Core_Vector4(const Core_Vector3<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; myW = (Type)1; }

	//DESTRUCTOR
	~Core_Vector4() {};

	//ASSIGNMENT
	void Set(Type aX, Type aY, Type aZ, Type aW) { myX = aX; myY = aY; myZ = aZ; myW = aW; }

	void Set(const Core_Vector3<Type>& aVec3, Type aW = Type(1)) { myX = aVec3.myX; myY = aVec3.myY; myZ = aVec3.myZ; myW = aW; }

	void SetVec3(const Core_Vector3<Type>& aVec3) { myX = aVec3.myX; myY = aVec3.myY; myZ = aVec3.myZ; }

	template <class AnotherType>
	Core_Vector4<Type>& operator=(const Core_Vector3<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; myW = Type(1); return *this; }

	template <class AnotherType>
	Core_Vector4<Type>& operator=(const Core_Vector4<AnotherType>& aCore_Vector) { myX = (Type)aCore_Vector.myX; myY = (Type)aCore_Vector.myY; myZ = (Type)aCore_Vector.myZ; myW = (Type)aCore_Vector.myW; return *this; }

	//MODIFYING OPERATORS
	Core_Vector4<Type>& operator+=(const Core_Vector4<Type>& aCore_Vector) { myX += aCore_Vector.myX; myY += aCore_Vector.myY; myZ += aCore_Vector.myZ; myW += aCore_Vector.myW; return *this; }
	Core_Vector4<Type>& operator-=(const Core_Vector4<Type>& aCore_Vector) { myX -= aCore_Vector.myX; myY += aCore_Vector.myY; myZ -= aCore_Vector.myZ; myW -= aCore_Vector.myW; return *this; }

	Core_Vector4<Type>& operator*=(Type aCore_Vector) { myX *= aCore_Vector; myY *= aCore_Vector; myZ *= aCore_Vector; myW *= aCore_Vector; return *this; }
	Core_Vector4<Type>& operator/=(Type aCore_Vector) { myX /= aCore_Vector; myY /= aCore_Vector; myZ /= aCore_Vector; myW /= aCore_Vector; return *this; }

	//CREATIVE OPERATORS
	Core_Vector4<Type> operator+(const Core_Vector4<Type>& aCore_Vector) const { return Core_Vector4<Type>(myX + aCore_Vector.myX, myY + aCore_Vector.myY, myZ + aCore_Vector.myZ, myW + aCore_Vector.myW); }
	Core_Vector4<Type> operator-(const Core_Vector4<Type>& aCore_Vector) const { return Core_Vector4<Type>(myX - aCore_Vector.myX, myY - aCore_Vector.myY, myZ - aCore_Vector.myZ, myW - aCore_Vector.myW); }

	Core_Vector4<Type>  operator*(Type aCore_Vector) const { return Core_Vector4<Type>(myX * aCore_Vector, myY * aCore_Vector, myZ * aCore_Vector, myW * aCore_Vector); }
	Core_Vector4<Type>  operator/(Type aCore_Vector) const { return Core_Vector4<Type>(myX / aCore_Vector, myY / aCore_Vector, myZ / aCore_Vector, myW / aCore_Vector); }

	//COMPARISON
	int operator==(const Core_Vector4<Type>& aCore_Vector) const { return (myX == aCore_Vector.myX && myY == aCore_Vector.myY && myZ == aCore_Vector.myZ && myW == aCore_Vector.myW); }
	int operator!=(const Core_Vector4<Type>& aCore_Vector) const { return !(*this == aCore_Vector); }

	//NEGATION
	Core_Vector4<Type> operator-() const { return Core_Vector4<Type>(-myX, -myY, -myZ, -myW); }

	//MATH
	Core_Vector4<Type>& MulElements(const Core_Vector4<Type>& aVect) { x *= aVect.x; y *= aVect.y; z *= aVect.z; w *= aVect.w; return *this; }
	Type Dot(const Core_Vector4<Type>& aCore_Vector) const { return aCore_Vector.myX * myX + aCore_Vector.myY * myY + aCore_Vector.myZ * myZ + aCore_Vector.myW * myW; }
	Type Length() const { return (Type)sqrt(myX * myX + myY * myY + myZ * myZ + myW * myW); }
	Type Length2() const { return (myX * myX + myY * myY + myZ * myZ + myW * myW); }
	Core_Vector4<Type>& Scale(Type aCore_Vector) { Normalize(); operator *= (aCore_Vector); return *this; }
	Core_Vector4<Type>& Normalize() { operator /= (Length()); return *this; }
	Core_Vector4<Type> GetNormalized() const { return *this / Length(); }
	Core_Vector4<Type>& NormalizeSafe() { if (Length2() > 0) Normalize(); return *this; }
	Core_Vector4<Type>& NormalizeSafe2() { if (Length2() > 0) Normalize(); else { x = y = z = 0; w = 1; } return *this; }
	Core_Vector4<Type> Unit() const { return Core_Vector4<Type>(*this).Normalize(); }
	Core_Vector4<Type> UnitSafe() const { return Core_Vector4<Type>(*this).NormalizeSafe(); }

	//VEC3 ACCESS
	Core_Vector3<Type>& Vec3() { return *(Core_Vector3<Type>*)this; }
	const Core_Vector3<Type>& Vec3() const { return *(const Core_Vector3<Type>*)this; }

	// ACCESS
	__forceinline Type operator[](int index) const { return (&x)[index]; }
	__forceinline Type& operator[](int index) { return (&x)[index]; }

	//MEMBERS
	union { Type myX; Type myR; Type myLeft; Type x; Type r; };
	union { Type myY; Type myG; Type myTop; Type y; Type g; };
	union { Type myZ; Type myB; Type myRight; Type z; Type b; };
	union { Type myW; Type myA; Type myBottom; Type w; Type a; };
};

template <class Type>
__forceinline Core_Vector3<Type> Core_Vector3<Type>::GetNormalizedSafe() const
{
	Type length = Length();

	if (length > 0)
		return *this / length;

	return *this;
}

template <class Type>
__forceinline Core_Vector3<Type>& Core_Vector3<Type>::NormalizeSafe()
{
	const Type length = Length();

	if (length > 0)
		*this /= length;

	return *this;
}

template <class Type>
__forceinline Core_Vector3<Type>& Core_Vector3<Type>::NormalizeFast()
{
	const float invlen = Core_InvSqrtFastSafe(Length2());

	x *= invlen;
	y *= invlen;
	z *= invlen;

	return *this;
}

template <class Type>
__forceinline Core_Vector3<Type>& Core_Vector3<Type>::NormalizeFastSafe()
{
	const float invlen = Core_InvSqrtFastSafe(Length2());

	x *= invlen;
	y *= invlen;
	z *= invlen;

	return *this;
}



//TYPEDEFS
//vector2
typedef Core_Vector2<int> Core_Vector2i;
typedef Core_Vector2<unsigned int> Core_Vector2ui;
typedef Core_Vector2<double> Core_Vector2d;
typedef Core_Vector2<float> Core_Vector2f;
typedef Core_Vector2<short> Core_Vector2s;

typedef Core_Vector2i Point2i;
typedef Core_Vector2ui Point2ui;
typedef Core_Vector2d Point2d;
typedef Core_Vector2f Point2f;

typedef Core_Vector2f TexCoord;

//vector3
typedef Core_Vector3<int> Core_Vector3i;
typedef Core_Vector3<double> Core_Vector3d;
typedef Core_Vector3<float> Core_Vector3f;
typedef Core_Vector3<unsigned char> Core_Vector3uc;
typedef Core_Vector3<short> Core_Vector3s;

typedef Core_Vector3i Point3i;
typedef Core_Vector3d Point3d;
typedef Core_Vector3f Point3f;

typedef Core_Vector3f Vertex;
typedef Core_Vector3f Normal;
typedef Core_Vector3f Color;
typedef Core_Vector3uc Core_Rgb;

//vector4
typedef Core_Vector4<int> Core_Vector4i;
typedef Core_Vector4<double> Core_Vector4d;
typedef Core_Vector4<float> Core_Vector4f;
typedef __declspec(align(16)) Core_Vector4<float> Core_Vector4fA;	// Aligned to 16-byte boundry for SSE optimizations
typedef Core_Vector4<unsigned char> Core_Vector4uc;
typedef Core_Vector4<short> Core_Vector4s;

typedef Core_Vector4i Point4i;
typedef Core_Vector4d Point4d;
typedef Core_Vector4f Point4f;

typedef Core_Vector4f ColorRGBA;
typedef Core_Vector4uc Core_Rgba;