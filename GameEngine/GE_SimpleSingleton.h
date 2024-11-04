#pragma once

template <typename T>
class GE_SimpleSingleton
{
public:
	GE_SimpleSingleton() = default;
	GE_SimpleSingleton(const GE_SimpleSingleton&) = delete;
	GE_SimpleSingleton& operator=(const GE_SimpleSingleton&) = delete;

public:
	static T& GetInstance()
	{
		static T ourInstance;
		return ourInstance;
	}
};