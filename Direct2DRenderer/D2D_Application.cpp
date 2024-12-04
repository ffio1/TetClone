#include "stdafx.h"
#include "D2D_Application.h"

//--------------------------------------------------------------------------------
std::size_t D2D_Application::D2D_Application::ColorBrushPairHash::operator()(const D2D1_COLOR_F& aColor) const
{
	int r = static_cast<int>(std::ceil(aColor.r * 255));
	int g = static_cast<int>(std::ceil(aColor.g * 255));
	int b = static_cast<int>(std::ceil(aColor.b * 255));
	int a = static_cast<int>(std::ceil(aColor.a * 255));

	std::size_t rBS = static_cast<std::size_t>(r & 0xff) << 24;
	std::size_t gBS = static_cast<std::size_t>(g & 0xff) << 16;
	std::size_t bBS = static_cast<std::size_t>(b & 0xff) << 8;
	std::size_t aBS = static_cast<std::size_t>(a & 0xff);
	return rBS + gBS + bBS + aBS;
}

//--------------------------------------------------------------------------------
bool D2D_Application::D2D_Application::ColorBrushPairEqual::operator()(const D2D1_COLOR_F& lhs, const D2D1_COLOR_F& rhs) const
{
	return lhs.r == rhs.r
		&& lhs.g == rhs.g
		&& lhs.b == rhs.b
		&& lhs.a == rhs.a;
}

//--------------------------------------------------------------------------------
D2D_Application::D2D_Application(const std::string& anApplicationName, const std::string& aWindowDescription, const Core_Vector2i& aWindowSize)
	: myApplicationName(anApplicationName)
	, myWindowDescription(aWindowDescription)
	, myWindowSize(aWindowSize)
	, myRenderTarget(nullptr)
	, myD2DFactory(nullptr)
	, myHwnd(NULL)
{
}

//--------------------------------------------------------------------------------
D2D_Application::~D2D_Application()
{
	CoUninitialize();
}

//--------------------------------------------------------------------------------
HRESULT D2D_Application::Initialize()
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		return hr;
	}

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &myD2DFactory);

	if (FAILED(hr))
	{
		return hr;
	}

	const std::wstring applicationName = std::wstring(myApplicationName.cbegin(), myApplicationName.cend());
	const std::wstring windowDescription = std::wstring(myWindowDescription.cbegin(), myWindowDescription.cend());

	WNDCLASSEX windowClass = { sizeof(WNDCLASSEX) };
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = D2D_Application::WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = sizeof(LONG_PTR);
	windowClass.hInstance = HINST_THISCOMPONENT;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	windowClass.lpszClassName = applicationName.c_str();
	RegisterClassEx(&windowClass);

	myHwnd = CreateWindow(
		applicationName.c_str(),
		windowDescription.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	if (!myHwnd)
	{
		return E_FAIL;
	}

	float dpi = static_cast<float>(GetDpiForWindow(myHwnd));
	int windowX = static_cast<int>(std::ceil(myWindowSize.x * dpi / 96.f));
	int windowY = static_cast<int>(std::ceil(myWindowSize.y * dpi / 96.f));
	SetWindowPos(myHwnd, NULL, NULL, NULL, windowX, windowY, SWP_NOMOVE);
	ShowWindow(myHwnd, SW_SHOWNORMAL);
	UpdateWindow(myHwnd);

	return hr;
}

//--------------------------------------------------------------------------------
void D2D_Application::Update()
{
	MSG message;

	if (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

//--------------------------------------------------------------------------------
HRESULT D2D_Application::CreateDeviceDependentResources()
{
	if (myRenderTarget)
	{
		return S_OK;
	}

	RECT rect;
	GetClientRect(myHwnd, &rect);

	D2D1_SIZE_U rectSize = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	HRESULT hr = myD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(myHwnd, rectSize),
		&myRenderTarget);

	if (FAILED(hr))
	{
		return hr;
	}

	std::array<D2D1::ColorF::Enum, 3> colorEnums = {
		D2D1::ColorF::LightSlateGray,
		D2D1::ColorF::CornflowerBlue,
		D2D1::ColorF::Red
	};

	for (const D2D1::ColorF::Enum& colorEnum : colorEnums)
	{
		ID2D1SolidColorBrush* colorBrush = nullptr;
		D2D1::ColorF color = D2D1::ColorF(colorEnum);
		myRenderTarget->CreateSolidColorBrush(color, &colorBrush);
		mySolidColorBrushes.insert({ color, colorBrush });
	}

	return hr;
}

//--------------------------------------------------------------------------------
void D2D_Application::ReleaseDeviceDependentResources()
{
	D2D_Utils::SafeRelease(&myRenderTarget);

	std::unordered_map<D2D1_COLOR_F, ID2D1SolidColorBrush*>::iterator it = mySolidColorBrushes.begin();
	for (; it != mySolidColorBrushes.end(); it++)
	{
		D2D_Utils::SafeRelease(&(*it).second);
	}

	mySolidColorBrushes.clear();
}

//--------------------------------------------------------------------------------
HRESULT D2D_Application::OnRender()
{
	HRESULT hr = CreateDeviceDependentResources();

	if (FAILED(hr))
	{
		return hr;
	}

	myRenderTarget->BeginDraw();
	myRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	myRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	ID2D1SolidColorBrush*& lightSlateGreyBrush = mySolidColorBrushes[D2D1::ColorF(D2D1::ColorF::LightSlateGray)];
	ID2D1SolidColorBrush*& redBrush = mySolidColorBrushes[D2D1::ColorF(D2D1::ColorF::Red)];

	// Tutorial Draw Logic
	{
		D2D1_SIZE_F renderTargetSize = myRenderTarget->GetSize();

		int width = static_cast<int>(renderTargetSize.width);
		int height = static_cast<int>(renderTargetSize.height);

		// Checkered Grid
		{
			for (int x = 0; x < width; x += 10)
			{
				myRenderTarget->DrawLine(
					D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
					D2D1::Point2F(static_cast<FLOAT>(x), renderTargetSize.height),
					lightSlateGreyBrush,
					0.5f
				);
			}

			for (int y = 0; y < height; y += 10)
			{
				myRenderTarget->DrawLine(
					D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
					D2D1::Point2F(renderTargetSize.width, static_cast<FLOAT>(y)),
					lightSlateGreyBrush,
					0.5f
				);
			}
		}

		// Boxes
		{
			D2D1_RECT_F rectangle1 = D2D1::RectF(
				renderTargetSize.width / 2 - 150.0f,
				renderTargetSize.height / 2 - 50.0f,
				renderTargetSize.width / 2 + 150.0f,
				renderTargetSize.height / 2 + 50.0f
			);

			D2D1_RECT_F rectangle2 = D2D1::RectF(
				renderTargetSize.width / 2 - 100.0f,
				renderTargetSize.height / 2 - 100.0f,
				renderTargetSize.width / 2 + 100.0f,
				renderTargetSize.height / 2 + 100.0f
			);

			myRenderTarget->FillRectangle(&rectangle1, lightSlateGreyBrush);
			myRenderTarget->FillRectangle(&rectangle2, redBrush);
		}
	}
	
	hr = myRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		ReleaseDeviceDependentResources();
	}
	
	return hr;
}

//--------------------------------------------------------------------------------
void D2D_Application::OnResize(UINT aWidth, UINT aHeight)
{
	if (!myRenderTarget)
	{
		return;
	}

	myRenderTarget->Resize(D2D1::SizeU(aWidth, aHeight));
}


//--------------------------------------------------------------------------------
LRESULT __stdcall D2D_Application::WndProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM anLParam)
{
	LRESULT result = 0;

	if (aMessage == WM_CREATE)
	{
		LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(anLParam);
		D2D_Application* application = static_cast<D2D_Application*>(createStruct->lpCreateParams);

		::SetWindowLongPtrW(
			aHwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(application)
		);

		return 1;
	}
	else
	{
		D2D_Application* application = reinterpret_cast<D2D_Application*>(
			static_cast<LONG_PTR>(::GetWindowLongPtrW(aHwnd, GWLP_USERDATA))
			);

		bool wasHandled = false;

		if (application)
		{
			switch (aMessage)
			{

			case WM_SIZE:
			{
				UINT width = LOWORD(anLParam);
				UINT height = HIWORD(anLParam);
				application->OnResize(width, height);
				result = 0;
				wasHandled = true;
				break;
			}

			case WM_DISPLAYCHANGE:
				InvalidateRect(aHwnd, NULL, FALSE);
				result = 0;
				wasHandled = true;
				break;

			case WM_PAINT:
				application->OnRender();
				ValidateRect(aHwnd, NULL);
				result = 0;
				wasHandled = true;
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				result = 1;
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(aHwnd, aMessage, aWParam, anLParam);
		}
	}

	return result;
}