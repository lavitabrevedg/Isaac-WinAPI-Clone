#pragma once

#include "Singleton.h"

class Texture;

enum class FontSize
{
	Font12 = 12,
	Font18 = 18,
	Font26 = 26,
};

// ���ҽ� ������ ���ӿ��� �پ��ϰ� ����.
// �ؽ�ó / �޽� / ���� / ����Ʈ ���..
// ��� ���ҽ����� �����ϴ� �Ŵ���
class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	void Init();
	void Destroy();	// ���ҽ� ����

	Texture* GetTextureInfo(string meshName);
	void LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount = 1, int32 yFrameCount = 1);

	HFONT GetFont(FontSize fontSize) 
	{
		auto iter = hFont.find(fontSize);
		if (iter != hFont.end())
			return iter->second;

		return nullptr; 
	}


private:
	unordered_map<string, Texture*> _textures;

	// ������� ������ ����
	unordered_map<FontSize, HFONT> hFont;
};

