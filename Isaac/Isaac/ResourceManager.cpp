#include "pch.h"
#include "ResourceManager.h"
#include "DXBitmap.h"
#include "Texture.h"	
#include "Sprite.h"
#include "Game.h"

void ResourceManager::Init(HWND hwnd, fs::path directory)
{
	_hwnd = hwnd;
	_resourcePath = directory;

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), (IUnknown**)&_dwriteFactory);
	
	{
		_spriteNames.emplace("titlemenu", SpriteInfo(0, 0, "titlemenu", true));
		_spriteNames.emplace("titlemenu2", SpriteInfo(0, 0, "titlemenu2", true));
		_spriteNames.emplace("titlemenu3", SpriteInfo(0, 0, "titlemenu3", true));
	}

	{
		//player
		_spriteNames.emplace("IsaacBody", SpriteInfo(0, 0, "IsaacBody", true));

		_spriteNames.emplace("IsaacHead", SpriteInfo(0, 0, "IsaacHead", true));
		_spriteNames.emplace("IsaaccyclopsHead", SpriteInfo(0, 0, "IsaaccyclopsHead", true));

		_spriteNames.emplace("A_Hurt", SpriteInfo(2, 1, "IsaacAction", true));
		_spriteNames.emplace("A_GetItem", SpriteInfo(1, 1, "IsaacAction", true));
		_spriteNames.emplace("A_Die", SpriteInfo(3, 0, "IsaacAction", true));
	}

	{
		//Tear
		_spriteNames.emplace("Tear", SpriteInfo(0, 0, "Tear", true));
	}

	{
		//UI
		_spriteNames.emplace("P_EmptyHeart",SpriteInfo(2,0,"Player_HP",true));
		_spriteNames.emplace("P_HalpHeart",SpriteInfo(1,0,"Player_HP",true));
		_spriteNames.emplace("P_Heart",SpriteInfo(0,0,"Player_HP",true));
		_spriteNames.emplace("Coin", SpriteInfo(0, 1, "crafting", true));
		_spriteNames.emplace("Boom", SpriteInfo(7, 1, "crafting", true));
		_spriteNames.emplace("Key", SpriteInfo(4, 1, "crafting", true));
		_spriteNames.emplace("MiniMapBoard", SpriteInfo(0, 0, "MiniMapBoard", true));
		_spriteNames.emplace("EmptyRoom", SpriteInfo(0, 0, "EmptyRoom", true));
	}

	{
		//room
		_spriteNames.emplace("Guid", SpriteInfo(0, 0, "Guid", true));
		_spriteNames.emplace("Tile", SpriteInfo(0, 0, "Tile", true));
		_spriteNames.emplace("Well", SpriteInfo(0, 0, "Well", true));
		_spriteNames.emplace("Well2", SpriteInfo(0, 0, "Well2", true));
		_spriteNames.emplace("Well3", SpriteInfo(0, 0, "Well3", true));
		_spriteNames.emplace("Well4", SpriteInfo(0, 0, "Well4", true));
		_spriteNames.emplace("Well5", SpriteInfo(0, 0, "Well5", true));
		_spriteNames.emplace("Well6", SpriteInfo(0, 0, "Well6", true));
		_spriteNames.emplace("Well7", SpriteInfo(0, 0, "Well7", true));
		_spriteNames.emplace("Well8", SpriteInfo(0, 0, "Well8", true));
		_spriteNames.emplace("Well9", SpriteInfo(0, 0, "Well9", true));
		_spriteNames.emplace("Door", SpriteInfo(0, 0, "Door", true));
		_spriteNames.emplace("GoldDoor", SpriteInfo(0, 0, "GoldDoor", true));
	}

	{
		//monster
		_spriteNames.emplace("Combat", SpriteInfo(0, 0, "Combat", true));
		_spriteNames.emplace("Fly", SpriteInfo(1, 1, "Fly", true));
		_spriteNames.emplace("Fly2", SpriteInfo(1, 1, "Fly2", true));
		_spriteNames.emplace("Monstrobase", SpriteInfo(1, 1, "Monstrobase", true));
		_spriteNames.emplace("gaperHead", SpriteInfo(0, 0, "gaperHead", true));
		_spriteNames.emplace("gaperBody", SpriteInfo(1, 1, "gaperBody", true));
	}

	{
		//Items
		_spriteNames.emplace("cyclops", SpriteInfo(5, 8, "Items", true));
		/*_spriteNames.emplace("1", SpriteInfo(4, 8, "Items", true));
		_spriteNames.emplace("2", SpriteInfo(6, 8, "Items", true));*/

		_spriteNames.emplace("Bomb", SpriteInfo(0, 0, "Bomb", true));
		_spriteNames.emplace("Bomb Animat", SpriteInfo(0, 0, "Bomb Animat", true));
		_spriteNames.emplace("Chest", SpriteInfo(0, 0, "Chest", true));
		_spriteNames.emplace("Heart", SpriteInfo(0, 0, "Heart", true));
		_spriteNames.emplace("Key", SpriteInfo(0, 0, "Key", true));
		_spriteNames.emplace("Penny1", SpriteInfo(0, 0, "Penny1", true));

		//object
		_spriteNames.emplace("rock", SpriteInfo(0, 0, "rock", true));
		_spriteNames.emplace("rocks", SpriteInfo(0, 0, "rocks", false));

		//effect
		_spriteNames.emplace("TearPop", SpriteInfo(1, 1, "TearPop", true));
		_spriteNames.emplace("bloodpoof", SpriteInfo(1, 1, "bloodpoof", true));
	}

	// font
	{
		loadFont();
	}

	// brush
	{
		createBrushes();
	}
}

void ResourceManager::Update(float deltaTime)
{

}

void ResourceManager::Destroy()
{
	for (auto& [key, res] : _bitmap)
	{
		delete res;
	}
	_bitmap.clear();

	for (auto& [key, res] : _fontCache)
	{
		SAFE_RELEASE(res);
	}
	_fontCache.clear();

	for (auto& [key, res] : _brushCache)
	{
		SAFE_RELEASE(res);
	}
	_brushCache.clear();

	SAFE_RELEASE(_fontCollection);
	SAFE_RELEASE(_fontSet);
	SAFE_RELEASE(_fontSetBuilder);
	SAFE_RELEASE(_dwriteFactory);
	SAFE_RELEASE(_fontFile);
}

DXBitmap* ResourceManager::LoadDXBitmap(string key, wstring path, int32 countX, int32 countY)
{
	if (_bitmap.find(key) != _bitmap.end())
	{
		// 이미 존재하는 키라면 리턴
		return _bitmap[key];
	}

	fs::path fullPath = _resourcePath / path;

	DXBitmap* bitmap = new DXBitmap();
	bitmap->Load(fullPath.c_str(), countX, countY);
	_bitmap[key] = bitmap;
	return bitmap;
}

DXBitmap* ResourceManager::GetDXBitmap(string key)
{
	if (_bitmap.find(key) != _bitmap.end())
	{
		// 이미 존재하는 키라면 리턴
		return _bitmap[key];
	}

	return nullptr;
}

const SpriteInfo* ResourceManager::GetSpriteInfo(string key)
{
	if (_spriteNames.find(key) != _spriteNames.end())
	{
		// 이미 존재하는 키라면 리턴
		return &_spriteNames[key];
	}
	return nullptr;
}

IDWriteTextFormat* ResourceManager::GetFont(FontSize fontSize)
{
	if (_fontCache.find(fontSize) != _fontCache.end())
	{
		// 이미 존재하는 키라면 리턴
		return _fontCache[fontSize];
	}
	return nullptr;
}

ID2D1SolidColorBrush* ResourceManager::GetBrush(BrushColor color)
{
	if (_brushCache.find(color) != _brushCache.end())
	{
		// 이미 존재하는 키라면 리턴
		return _brushCache[color];
	}
	return nullptr;
}

void ResourceManager::AddSpriteINfo(string key, SpriteInfo info)
{
	_spriteNames.emplace(key, info);
}

bool ResourceManager::loadFont()
{
	fs::path fullPath = _resourcePath / L"Font/MaplestoryLight.ttf";
	HRESULT hr;

	hr = _dwriteFactory->CreateFontFileReference(
		fullPath.c_str(),  // 경로
		nullptr,                   // 마지막 수정시간 (nullptr이면 현재 파일 기준)
		&_fontFile
	);
	if (FAILED(hr)) return false;

	hr = _dwriteFactory->CreateFontSetBuilder(&(_fontSetBuilder));
	if (FAILED(hr)) return false;

	_fontSetBuilder->AddFontFile(_fontFile);

	hr = _fontSetBuilder->CreateFontSet(&_fontSet);
	if (FAILED(hr)) return false;

	hr = _dwriteFactory->CreateFontCollectionFromFontSet(_fontSet, &_fontCollection);
	if (FAILED(hr)) return false;

	IDWriteFontFamily* fontFamily = nullptr;
	_fontCollection->GetFontFamily(0, &fontFamily);

	IDWriteLocalizedStrings* pFamilyNames = nullptr;
	fontFamily->GetFamilyNames(&pFamilyNames);

	UINT32 index = 0;
	BOOL exists = FALSE;
	pFamilyNames->FindLocaleName(L"ko-kr", &index, &exists);
	if (!exists) index = 0;

	WCHAR familyName[100] = {};
	pFamilyNames->GetString(index, familyName, 100);

	// 사이즈에 맞게 폰트 생성
	auto createFont = [&](FontSize size)
		{
			int32 fontSize = (int32)size;
			IDWriteTextFormat* textFormat = nullptr;
			HRESULT hr = _dwriteFactory->CreateTextFormat(
				familyName, _fontCollection,
				DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL, (float)fontSize, L"ko-kr",
				&textFormat
			);
			if (FAILED(hr)) return false;

			_fontCache[size] = textFormat;
			return true;
		};

	createFont(FontSize::FONT_12);
	createFont(FontSize::FONT_16);
	createFont(FontSize::FONT_20);
	createFont(FontSize::FONT_30);

	SAFE_RELEASE(pFamilyNames);
	SAFE_RELEASE(fontFamily);
	return SUCCEEDED(hr);
}

bool ResourceManager::createBrushes()
{
	ID2D1HwndRenderTarget* renderTarget = Game::GetInstance()->GetRenderTarget();
	if (nullptr == renderTarget)
		return false;

	{
		ID2D1SolidColorBrush* brush = nullptr;
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);
		_brushCache[BrushColor::Red] = brush;
	}
	{
		ID2D1SolidColorBrush* brush = nullptr;
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
		_brushCache[BrushColor::White] = brush;
	}
	return false;
}

void ResourceManager::createSpriteNameInfo(string spriteName, int32 xCount, int32 totalCount, wstring bitmapKey)
{
}
