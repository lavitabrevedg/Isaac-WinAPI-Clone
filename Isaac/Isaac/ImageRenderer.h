#pragma once

#include "Component.h"
class Texture;

class ImageRenderer : public Component
{
	using Super = Component;
public:
	ImageRenderer(string textureKey);

	virtual void InitCompoent() override;
	virtual void UpdateComponent(float deltaTime) override;
	virtual void RenderComponent(HDC hdc, Vector pos) override;

	int32 GetTextureWidth();
	Texture* GetTexture() { return _textureInfo; }
	void SetApplyCameraPos(bool apply) { _applyCameraPos = apply; }

private:
	Texture* _textureInfo = nullptr;	// ���ҽ� �Ŵ����� ���ؼ� ������ ���� : ���� �ڻ�
	bool _applyCameraPos = true;
};


