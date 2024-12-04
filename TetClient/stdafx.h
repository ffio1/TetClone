#pragma once

// Standard library includes
#include <array>
#include <unordered_map>
#include <string>
#include <vector>

// Platform includes
#include <windows.h>

// External dependency includes

// Lower-level libaries
#include "Core_Math.h"
#include "Core_Vector.h"

// Engine Includes
#include "GE_GlobalDefines.h"
#include "GE_Logger.h"
#include "GE_StringUtils.h"

// Application Includes
#include "TetClient_GlobalDefines.h"

#ifdef USE_RENDERER_DIRECT2D
#include "d2d1.h"
#endif