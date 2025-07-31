#pragma once

// �ؽ�ó�� �׸��� ����
// �Ѱ����� �������� ����ϱ� ���� �����丵
class Texture
{
public:
	Texture();

	void Load(string key, string texturePath, int32 transparent, int32 xFrameCount = 1, int32 yFrameCount = 1);
	void Render(HDC hdc, Vector pos, Vector src, Vector rederSize, bool applyCameraPos = true);

	int32 GetTextureWidth()
	{
		return _sizeX;
	}

public:
	// �ؽ�ó�� �׸������� ����
	HDC			_textureHdc = 0;
	HBITMAP		_bitmap;
	int32		_transparent = -1;	// �����ϰ� �������ϴ� ����
	int32		_sizeX = 0;
	int32		_sizeY = 0;
	int32		_frameCountX = 0;	// X������ ��� �������� �ִ���
	int32		_frameCountY = 0;	// Y������ ��� �������� �ִ���
};

