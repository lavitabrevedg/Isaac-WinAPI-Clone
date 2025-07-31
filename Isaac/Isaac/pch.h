#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
#include <functional>	// std::function
#include <algorithm>	// std::find_if, std::sort

// C++ 20
#include <format>		// std::format("x:{0}, y:{1}"
#include <numbers>  
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

// transparent Blt
#pragma comment(lib, "msimg32.lib")

// GDI+
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;


// Direct 2D
#include <d2d1.h>
#include <dwrite_1.h>
#include <dwrite_3.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

// Json
#include "Json/nlohmann/json.hpp" // nlohmann/json ��� ����
using json = nlohmann::json;

// magic_enum
#include "magic_enum/magic_enum.hpp"


using namespace std;

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

// �޸� ��. json ���̺귯�� ���ʿ��� �ؾ��� new Ű����� �浹���� �ʴ´�.
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

// ���� ����� 
#include "Defines.h"