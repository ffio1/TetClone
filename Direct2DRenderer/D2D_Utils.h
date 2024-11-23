#pragma once

namespace D2D_Utils
{
	template <typename T>
	inline void SafeRelease(T** anInterfaceToRelease)
	{
		if (!anInterfaceToRelease)
		{
			return;
		}

		(*anInterfaceToRelease)->Release();
		(*anInterfaceToRelease) = nullptr;
	}

	EXTERN_C IMAGE_DOS_HEADER __ImageBase;
	#define HINST_THISCOMPONENT ((HINSTANCE)&D2D_Utils::__ImageBase)
}