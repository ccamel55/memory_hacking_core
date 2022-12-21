#pragma once

#include "singleton.hpp"
#include "macos.hpp"

#include "cryptography/fn1v.hpp"

#include "config/Config.hpp"

#include "keybinds/Keybinds.hpp"

#include "math/FastMath.hpp"
#include "math/RayIntersection.hpp"
#include "math/MathLib.hpp"

#include "memory/DetourHookManager.hpp"
#include "memory/PatternScanner.hpp"
#include "memory/VirtualFnHookManager.hpp"

#include "rendering/BitmapFont.hpp"
#include "rendering/directx9/Directx9Render.hpp"

#include "threading/ThreadPool.hpp"
#include "threading/TrippleBuffer.hpp"

#include "type/Color.hpp"
#include "type/matrix/Matrix3x4.hpp"
#include "type/matrix/Matrix4x4.hpp"
#include "type/vector/Vector2D.hpp"
#include "type/vector/Vector3D.hpp"

#include "ui/Ui.hpp"

#include "win32/Console.hpp"
#include "win32/InputHandler.hpp"