#pragma once
class Texture
{
public:
	void Load(wstring fileName, int32 maxCountX, int32 maxCountY, int32 transparent, RenderLayer type);
	void Destroy();

	void Render(HDC hdc, Vector pos, Vector srcpos);

	void SetCenterAlign(bool center) { _centerAlign = center; }
	void SetSize(int32 x, int32 y) { _sizeX = x; _sizeY = y; }

	int32 GetSizeX() { return _sizeX; }
	int32 GetSizeY() { return _sizeY; }

	Size GetFrameSize() { return Size(_frameSizeX, _frameSizeY); }
	void GetFrameCount(int32& outX, int32& outY) { outX = _maxCountX; outY = _maxCountY; }

private:
	HDC _textureHdc = 0;
	HBITMAP _bitmap;

	int32 _transparent = -1;
	int32 _textureSizeX = 0;
	int32 _textureSizeY = 0;

	int32 _sizeX = 0;
	int32 _sizeY = 0;

	int32 _maxCountX = 0;
	int32 _maxCountY = 0;
	int32 _frameSizeX = 0;
	int32 _frameSizeY = 0;

	bool _centerAlign = true;
};

