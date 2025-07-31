#include "pch.h"
#include "Texture.h"

void Texture::Load(wstring fileName, int32 maxCountX, int32 maxCountY, int32 transparent, RenderLayer type)
{
	fs::path fullPath = fs::current_path() / L"../Resources/Image/" / fileName; //@TODO type에 따라 파일명이 달라서 그럴려 했는데 json으로 해야할것같다.
}

void Texture::Destroy()
{
}

void Texture::Render(HDC hdc, Vector pos, Vector srcpos)
{
}
