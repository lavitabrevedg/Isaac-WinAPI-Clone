#pragma once

#include "Component.h"

class Texture;

// �� �ؽ�ó �׸��Ⱑ �ƴ϶�, �ϳ��� �����Ӵ����� �׸��� ��ü
class SpriteRenderer : public Component
{
	using Super = Component;

public:
	SpriteRenderer(string textureKey, float dur);

	virtual void InitCompoent() override;
	virtual void UpdateComponent(float deltaTime) override;
	virtual void RenderComponent(HDC hdc, Vector pos) override;

	void SetFrameX(int32 x) { _frameX = x; }
	void SetFrameY(int32 y) { _frameY = y; }

	int32 GetRenderSizeX() { return _renderSizeX; }
	bool IsEnd() { return _isEnd; }
	void SetApplyCameraPos(bool apply) { _applyCameraPos = apply; }

private:
	Texture* _textureInfo = nullptr;	// ���ҽ� �Ŵ����� ���ؼ� ������ ���� : ���� �ڻ�

	// ���� �ؽ�ó�� ���� � �������� �׸��� �ִ���
	int32 _frameX = 0;
	int32 _frameY = 0;

	// �� �����Ӵ� ������
	int32 _renderSizeX = 0;
	int32 _renderSizeY = 0;

	bool  _isEnd = false;

	float _durtaion = 0;
	float _sumTime = 0;

	bool _applyCameraPos = true;
};

