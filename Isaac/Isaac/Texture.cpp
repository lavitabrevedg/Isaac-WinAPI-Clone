#include "pch.h"
#include "Texture.h"

void Texture::Load(wstring fileName, int32 maxCountX, int32 maxCountY, int32 transparent, RenderLayer type)
{
	fs::path fullPath = fs::current_path() / L"../Resources/Image/" / fileName; //@TODO type�� ���� ���ϸ��� �޶� �׷��� �ߴµ� json���� �ؾ��ҰͰ���.
}

void Texture::Destroy()
{
}

void Texture::Render(HDC hdc, Vector pos, Vector srcpos)
{
}
