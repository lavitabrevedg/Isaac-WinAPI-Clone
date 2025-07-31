#include "pch.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer(string textureKey, float dur)
{
	_textureInfo = ResourceManager::GetInstance()->GetTextureInfo(textureKey);
	_durtaion = dur;

	// �� �������� ����� �̸� ���
	//@TODO : TextureInfo �� �߰��ϴ°� ��� : ���� �ڻ�. ��ü���� �ٸ��� ���������� ����
	if (_textureInfo)
	{
		int32 renderSizeX = _textureInfo->_frameCountX != 0 ? (_textureInfo->_sizeX / _textureInfo->_frameCountX) : _textureInfo->_sizeX;
		int32 renderSizeY = _textureInfo->_frameCountY != 0 ? (_textureInfo->_sizeY / _textureInfo->_frameCountY) : _textureInfo->_sizeY;
		
		_renderSizeX = renderSizeX;
		_renderSizeY = renderSizeY;
	}
}

void SpriteRenderer::InitCompoent()
{
	Super::InitCompoent();
}

void SpriteRenderer::UpdateComponent(float deltaTime)
{
	Super::UpdateComponent(deltaTime);

	if (_durtaion == 0)
		return;

	if (_isEnd)
		return;

	if (_textureInfo == nullptr)
		return;

	// ������ ������ ����� �ϴ� ����
	_sumTime += deltaTime;

	int32 totalCount = _textureInfo->_frameCountX * _textureInfo->_frameCountY;
	float delta = _durtaion / totalCount;

	// ���� �ð��� ������ ���� ������ �̵�
	if (_sumTime >= delta && _isEnd == false)
	{
		if (_frameX + 1 >= _textureInfo->_frameCountX)
		{
			_frameX = 0;

			if (_frameY + 1 >= _textureInfo->_frameCountY)
			{
				_frameY = 0;

				//if (bitmapInfo->loop == false)
				{
					_isEnd = true;
				}
			}
			else
			{
				++_frameY;
			}
		}
		else
		{
			++_frameX;
		}

		_sumTime -= delta;
	}
}

void SpriteRenderer::RenderComponent(HDC hdc, Vector pos)
{
	Super::RenderComponent(hdc, pos);

	if (_textureInfo == nullptr)
		return;

	// �����ؽ�ó�� ���� ��ġ�� ����Ѵ�.
	// �ؽ�ó�� Ư�� frame ���� �׷��� �ؼ�
	int32 srcX = _frameX * _renderSizeX;
	int32 srcY = _frameY * _renderSizeY;

	_textureInfo->Render(hdc, pos, Vector(srcX, srcY), Vector(_renderSizeX, _renderSizeY), _applyCameraPos);
}
