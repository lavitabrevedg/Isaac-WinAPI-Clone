#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "Sprite.h"

Block::Block(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);
	CreateRectCollider(GridSize, GridSize);
}

Block::Block()
{
}

Block::Block(Sprite* sprite)
{
	_sprite = sprite;
}

void Block::Init(Vector pos)
{
	_pos = pos;
	Super::Init(pos);
}

void Block::Destroy()
{
	Super::Destroy();
}

void Block::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Block::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->RenderImage(_dxRenderTarget,_pos);
	Super::Render(_dxRenderTarget);
}

void Block::LoadActor(std::wistringstream& steam)
{
	// �̹� ���Ͱ� �����Ǿ��ٴ°� �ش� file stream ���� actorType�� ���� ���� ���� �����̴�.
	wchar_t comma = ',';
	steam >> comma;	// GetActorType() �������� ������ �б�

	int32 indexX = 0, indexY = 0;
	//steam >> indexX >> comma >> indexY >> comma;

	int32 x = 0, y = 0;
	steam >> x >> comma >> y >> comma;

	int32 w, h;
	steam >> w >> comma >> h >> comma;

	wstring wspriteName;
	std::getline(steam, wspriteName);

	std::string spriteName;
	spriteName.assign(wspriteName.begin(), wspriteName.end());

	Vector pos = Vector(x, y);
	SetPos(pos);
	_sprite = CreateSpriteComponent(spriteName, w, h);
	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height);
}