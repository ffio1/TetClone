#pragma once

// Standard libraries
#include <array>
#include <unordered_map>
#include <mutex>
#include <string>
#include <vector>

// GE Utils
#include "GE_GlobalDefines.h"
#include "GE_SimpleSingleton.h"
#include "GE_StringUtils.h"

#ifdef USE_RENDERER_DIRECT2D
#include "Windows.h"
#include "d2d1.h"
#endif