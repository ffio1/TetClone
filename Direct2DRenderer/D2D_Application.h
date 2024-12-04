#pragma once

#include "Core_Vector.h"

class D2D_Application
{
public:
	D2D_Application(const std::string& anApplicationName, const std::string& aWindowDescription, const Core_Vector2i& aWindowSize);
	~D2D_Application();

public:
	HRESULT Initialize();
	void Update();

private:
	HRESULT CreateDeviceDependentResources();

	void ReleaseDeviceDependentResources();

	HRESULT OnRender();
	void OnResize(UINT aWidth, UINT aHeight);

	static LRESULT __stdcall WndProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM anLParam);

private:
	struct ColorBrushPairHash
	{
		std::size_t operator()(const D2D1_COLOR_F& aColor) const;
	};

	struct ColorBrushPairEqual
	{
		bool operator()(const D2D1_COLOR_F& lhs, const D2D1_COLOR_F& rhs) const;
	};

private:
	HWND myHwnd;
	ID2D1Factory* myD2DFactory;
	ID2D1HwndRenderTarget* myRenderTarget;
	std::unordered_map<D2D1_COLOR_F, ID2D1SolidColorBrush*, ColorBrushPairHash, ColorBrushPairEqual> mySolidColorBrushes;

	std::string myApplicationName;
	std::string myWindowDescription;
	Core_Vector2i myWindowSize;
};