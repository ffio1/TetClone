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

// A modified version of massgate's Core_StaticArray.h

template <typename Type, int Size>
class Core_StaticArray
{
public:
	__forceinline Core_StaticArray() {}

	__forceinline const Type& operator[] (const int anIndex) const
	{
		return myItemList[anIndex];
	}

	__forceinline Type& operator[] (const int anIndex)
	{
		return myItemList[anIndex];
	}

	__forceinline bool operator == (const Core_StaticArray& anArray) const
	{
		for (int i = 0; i < Size; i++)
			if (!(myItemList[i] == anArray.myItemList[i]))
				return false;

		return true;
	}

	__forceinline bool operator != (const Core_StaticArray& anArray) const
	{
		for (int i = 0; i < Size; i++)
			if (myItemList[i] != anArray.myItemList[i])
				return true;

		return false;
	}

	__forceinline Type* GetBuffer() { return myItemList; }
	__forceinline const Type* GetBuffer() const { return myItemList; }

	static int Count() { return Size; }

protected:
	Type myItemList[Size];

private:
	// Copy constructor not allowed. To avoid duplicating the array by mistake.
	Core_StaticArray(const Core_StaticArray& anArray);
};

template <typename Type, int Size, int Size2>
class Core_StaticArray2 : public Core_StaticArray< Core_StaticArray<Type, Size2>, Size >
{
};

template <typename Type, int Size, int Size2, int Size3>
class Core_StaticArray3 : public Core_StaticArray< Core_StaticArray< Core_StaticArray<Type, Size3>, Size2>, Size >
{
};