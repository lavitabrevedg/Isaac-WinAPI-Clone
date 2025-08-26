#include "pch.h"
#include "Sprite.h"
#include "Game.h"
#include "ResourceManager.h"
#include "DXBitmap.h"

Sprite::Sprite(string key, int32 width, int32 height, bool alignCenter) : Super(key, width, height)
{
	_alignCenter = alignCenter;
}

Sprite::~Sprite()
{

}

void Sprite::UpdateComponent(float deltaTime)
{

}


void Sprite::RenderComponent(ID2D1RenderTarget* _dxRenderTarget)
{
	Dimension frameSize = _bitmap->GetFrameSize();

	// �ҽ� ��Ʈ�ʿ��� ������ ���� ��ǥ ���
	float srcX = _indexX * (float)_bitmap->GetFrameSize().Width;
	float srcY = _indexY * (float)_bitmap->GetFrameSize().Height;

	// ���� ��Ʈ�ʿ��� �׸� ���� (�ҽ� ����)
	D2D1_RECT_F srcRect = D2D1::RectF(
		srcX + 1.0f,
		srcY + 1.0f,
		srcX + _bitmap->GetFrameSize().Width - 1.0f,
		srcY + _bitmap->GetFrameSize().Height - 1.0f);

	Vector offset = _getFrameOffset(this);
	if (_flip) offset.x = -offset.x;
	Vector drawPos = _pos + offset;

	// ȭ�鿡 �������� ��ġ�� ũ�� (��� ����)
	D2D1_RECT_F destRect;
	if (_alignCenter)
	{
		destRect = D2D1::RectF(
			roundf(drawPos.x - _size.Width * 0.5f),
			roundf(drawPos.y - _size.Height * 0.5f),
			roundf(drawPos.x + _size.Width * 0.5f),
			roundf(drawPos.y + _size.Height * 0.5f));
	}
	else
	{
		destRect = D2D1::RectF(
			roundf(drawPos.x),
			roundf(drawPos.y),
			roundf(drawPos.x + _size.Width),
			roundf(drawPos.y + _size.Height));
	}

	// ���� ��ȯ ���� ����
	D2D1::Matrix3x2F originalTransform;
	_dxRenderTarget->GetTransform(&originalTransform);

	D2D1::Matrix3x2F finalTransform = originalTransform;
	D2D1::Matrix3x2F scaleTransform = D2D1::Matrix3x2F::Scale(
		D2D1::SizeF(1.0f, 1.0f),
		D2D1::Point2F(drawPos.x, drawPos.y) // ���� ������
	);
	finalTransform = scaleTransform * finalTransform;

	// �¿� ���� ��ȯ ��� ����
	if (_flip) // dirX�� ������ ��� �¿� ����
	{
		D2D1::Matrix3x2F flipTransform = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(-1.0f, 1.0f), // X�� ����, Y�� �״��
			D2D1::Point2F(drawPos.x, drawPos.y) // ���� ������
		);
		finalTransform = flipTransform * finalTransform;
	}
	// ȸ�� ��� ����
	if (_rotate != 0)
	{
		D2D1::Matrix3x2F rotate = D2D1::Matrix3x2F::Rotation(
			_rotate,
			D2D1::Point2F(drawPos.x, drawPos.y)
		);
		finalTransform = rotate * finalTransform;
	}

	// ���� ��ȯ
	_dxRenderTarget->SetTransform(finalTransform);

	// ��Ʈ�� ������
	_dxRenderTarget->DrawBitmap(_bitmap->GetBitmap(), destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &srcRect);

	// ���� ��ȯ ���� ����
	_dxRenderTarget->SetTransform(originalTransform);

}
//
//Size Sprite::GetFrameSize()
//{
//	return Dimension();
//}

void Sprite::GetFrameCount(int32& outX, int32& outY)
{
	outX = 0;
	outY = 0;

	if (_bitmap)
	{
		_bitmap->GetFrameCount(outX, outY);
	}
}

void Sprite::SetFrameOffset(int fx, int fy, Vector offset)
{
	int cntX = 0, cntY = 0;
	if (_bitmap) _bitmap->GetFrameCount(cntX, cntY);
	int key = fy * max(1, cntX) + fx;
	_frameOffsets[key] = offset;
}

Vector Sprite::_getFrameOffset(const Sprite* s)
{
	int cntX = 0, cntY = 0;
	if (s->_bitmap) s->_bitmap->GetFrameCount(cntX, cntY);
	int key = s->_indexY * max(1, cntX) + s->_indexX;
	auto it = s->_frameOffsets.find(key);
	return(it != s->_frameOffsets.end()) ? it->second : Vector{ 0,0 };
}


//------------------------------------------------------------------------

