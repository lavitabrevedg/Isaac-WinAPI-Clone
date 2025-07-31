#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Game.h"

void ResourceManager::Init()
{
    // �ܺ� ��Ʈ�� �ý��ۿ� �ӽ÷� ���
    //FR_PRIVATE: �ý��� ��ü�� �ƴ� ���� ���μ��������� ���
    //AddFontResourceEx((directory / L"Font/MaplestoryLight.ttf").c_str(), FR_PRIVATE, 0);

    // win API 
    auto createMyFont = [this](FontSize fontSize)
        {
            hFont[fontSize] = CreateFont(
                (int32)fontSize, 0, 0, 0, FW_NORMAL,
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"�����ý��丮"  // Family �̸�!
            );
        };

    createMyFont(FontSize::Font12);
    createMyFont(FontSize::Font18);
    createMyFont(FontSize::Font26);
     
    // ������ �ʿ��� �ؽ�ó�� ���ؼ� �ε��Ѵ�.
    //{
    //    Texture* texture = new Texture();
    //    texture->Load(L"Player.bmp", RGB(252, 0, 255));
    //    _textures["Player"] = texture;
    //}
    //{
    //    Texture* texture = new Texture();
    //    texture->Load(L"PlayerBullet.bmp", RGB(255, 0, 255));
    //    _textures["PlayerBullet"] = texture;
    //}
}

void ResourceManager::Destroy()
{
    for (auto iter : _textures)
    {
        delete iter.second;
    }
    _textures.clear();
}

Texture* ResourceManager::GetTextureInfo(string meshName)
{
    // ��ü������ �����ϰ� �ִ� ��� ���θ޽��߿� meshName �ش��ϴ� ���ҽ��� ��ȯ�Ѵ�.
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // �ε��� �ȵưų�, �̸��� �߸��ưų�
    return nullptr;
}

void ResourceManager::LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
    Texture* texture = new Texture();
    texture->Load(key, texturePath, transparent, xFrameCount, yFrameCount);
    _textures[key] = texture;
}