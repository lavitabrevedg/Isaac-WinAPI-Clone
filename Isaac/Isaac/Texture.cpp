#include "pch.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Camera.h"

Texture::Texture()
{
}

void Texture::Load(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
	fs::path fullPath = fs::current_path() / L"../Resources/" / texturePath;

	HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

	_textureHdc = ::CreateCompatibleDC(hdc);
	_bitmap = (HBITMAP)::LoadImageW(
		nullptr,
		fullPath.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);
	if (_bitmap == 0)
	{
		::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
		return;
	}

	_transparent = transparent; //RGB(252, 0, 255);

	HBITMAP prev = (HBITMAP)::SelectObject(_textureHdc, _bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);

	_sizeX = bit.bmWidth;
	_sizeY = bit.bmHeight;

	_frameCountX = xFrameCount;
	_frameCountY = yFrameCount;
}

void Texture::Render(HDC hdc, Vector pos, Vector src, Vector rederSize, bool applyCameraPos)
{
	// �׸��� �׸��µ�, pos ��ġ�� �׸��� �׸���.
	// pos ���� ��ǥ��(�� ������ ���� ��ǥ)
	// ī�޶� �������� ��ǥ ��ȯ�� ���ش�.

	Vector screenPos = applyCameraPos ? Camera::ConvertScreenPos(pos) : pos;


	if (_transparent == -1)
	{
		::BitBlt(hdc,	// ����ۿ�
			(int32)screenPos.x - (rederSize.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
			(int32)screenPos.y - (rederSize.y / 2),
			rederSize.x,
			rederSize.y,
			_textureHdc,	// �ؽ��� �׸���
			src.x,
			src.y,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - (rederSize.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
			(int32)screenPos.y - (rederSize.y / 2),
			rederSize.x,							// �ؽ��İ� �׷������ϴ� ũ�� width		// 64
			rederSize.y,							// �ؽ��İ� �׷������ϴ� ũ�� height	// 64
			_textureHdc,					// �ؽ�ó�� ����
			src.x,								// ���� �ؽ����� X						// 0~15���� �ε����� ���ư��鼭 �׷����Ѵ�.
			src.y,								// ���� �ؽ����� Y	
			rederSize.x,							// ���� �ؽ����� width					// 64
			rederSize.y,							// ���� �ؽ����� height					// 64
			_transparent);	// ������� �����ϰ� �׸���
	}

	//if (transparent == -1)
	//{
	//	::BitBlt(hdc,	// ����ۿ�
	//		(int32)pos.x - (sizeX / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
	//		(int32)pos.y - (sizeY / 2),
	//		sizeX,
	//		sizeY,
	//		textureHdc,	// �ؽ��� �׸���
	//		0,
	//		0,
	//		SRCCOPY);
	//}
	//else
	//{
	//	::TransparentBlt(hdc,
	//		(int32)pos.x - (sizeX / 2),	// �ؽ��İ� �׷������ϴ� ��ǥ X			// pos.x
	//		(int32)pos.y - (sizeY / 2),	// �ؽ��İ� �׷������ϴ� ��ǥ Y			// pos.y
	//		sizeX,							// �ؽ��İ� �׷������ϴ� ũ�� width		// 64
	//		sizeY,							// �ؽ��İ� �׷������ϴ� ũ�� height	// 64
	//		textureHdc,					// �ؽ�ó�� ����
	//		0,								// ���� �ؽ����� X						// 0~15���� �ε����� ���ư��鼭 �׷����Ѵ�.
	//		0,								// ���� �ؽ����� Y	
	//		sizeX,							// ���� �ؽ����� width					// 64
	//		sizeY,							// ���� �ؽ����� height					// 64
	//		transparent);	// ������� �����ϰ� �׸���
	//}
}