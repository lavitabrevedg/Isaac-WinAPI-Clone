#include "pch.h"
#include "Monster.h"
#include "Sprite.h"
#include "Game.h"
#include "PlayScene.h"
#include "TimeManager.h"

Monster::Monster()
{
	_bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,true,0.1f };

	_bodyAnim[BodyState::B_WALK][DirType::DIR_DOWN] = AnimInfo{ 0,0,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_UP] = AnimInfo{ 0,0,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_RIGHT] = AnimInfo{ 0,1,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_LEFT] = AnimInfo{ 0,1,10,1,true,0.1f,true };

	_Body = CreateSpriteComponent("gaperBody", 50, 35);
	_sprite = CreateSpriteComponent("gaperHead", 55, 60);

	_Body->SetFrameOffset(0, 0, { 9, 0 });
	_Body->SetFrameOffset(1, 0, { 7, 0 });
	_Body->SetFrameOffset(2, 0, { 6, 0 });
	_Body->SetFrameOffset(3, 0, { 5, 0 });
	_Body->SetFrameOffset(4, 0, { 4, 0 });
	_Body->SetFrameOffset(5, 0, { -3, 0 });
	_Body->SetFrameOffset(6, 0, { -4, 0 });
	_Body->SetFrameOffset(7, 0, { -5, 0 });
	_Body->SetFrameOffset(8, 0, { -6, 0 });
	_Body->SetFrameOffset(9, 0, { -7, 0 });

	_Body->SetFrameOffset(0, 1, { 9, 0 });
	_Body->SetFrameOffset(1, 1, { 8, 0 });
	_Body->SetFrameOffset(2, 1, { 7, 0 });
	_Body->SetFrameOffset(3, 1, { 6, 0 });
	_Body->SetFrameOffset(4, 1, { 5, 0 });
	_Body->SetFrameOffset(5, 1, { -2, 0 });
	_Body->SetFrameOffset(6, 1, { -3, 0 });
	_Body->SetFrameOffset(7, 1, { -4, 0 });
	_Body->SetFrameOffset(8, 1, { -5, 0 });
	_Body->SetFrameOffset(9, 1, { -6, 0 });

	AnimInfo base = _bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN];
	_bodyAnimCtrl.SetAnim(base);

	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height + _Body->GetSize().Height - 30);
}

Monster::~Monster()
{
}

void Monster::Destroy()
{
	Super::Destroy();
}

void Monster::Init(Vector pos)
{
	Super::Init(pos);
	_maxSpeed = 250.f;
	_friction = 0.95f;
	_velocity = { 0,0 };
	_acceleration = { 0,0 };

	_maxhp = 25;
	_hp = _maxhp;

	_currbodyDir = DirType::DIR_DOWN;
}

void Monster::Update(float deltatime)
{
	now = TimeManager::GetInstance()->GetNow();

	_currCount++;

	if (_checkCount < _currCount)
	{
		if (this == nullptr)
			return;

		Cell start = Cell::ConvertToCell(this->GetPos(), GridSize);
		Vector player = PlayScene::GetGameScene()->GetPlayerPos();
		Cell end = Cell::ConvertToCell(player, GridSize);

		PlayScene::GetGameScene()->FindPath(start, end, _path);

		if (!_path.empty() && _path.front().index_X == start.index_X &&
			_path.front().index_Y == start.index_Y)
			_pathIdx = 1;

		_currCount = 0;
	}

	float moveForce = 500.f;
	bool moving = false;

	if (_pathIdx < (int)_path.size())
	{
		Vector target = Cell::ConvertToWorld(_path[_pathIdx], GridSize);
		Vector toT = target - _pos;
		float dist = toT.LengthSquared();

		if (dist <= _arrive * _arrive)
		{
			++_pathIdx;
			/*target = Cell::ConvertToWorld(_path[_pathIdx], GridSize);
			toT = target - _pos;*/
		}

		Vector dir = toT.GetNormalize();
		_acceleration += dir * moveForce;
		moving = true;

		UpdateFacingFromDir(dir);
	}

	Super::Update(deltatime);

	if (_currbodyDir != _prevbodyDir) {
		AnimInfo bodyInfo = _bodyAnim[B_WALK][_currbodyDir];
		_bodyAnimCtrl.SetAnim(bodyInfo);
		_prevbodyDir = _currbodyDir;
	}

	_bodyAnimCtrl.Update(deltatime, _Body);
}

void Monster::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	if (_attacedTime > now)
		return;

	_Body->SetPos(_pos + Vector{ 0,13 });
	_sprite->SetPos(_pos + Vector{ 0,-13 });
	Super::Render(_dxRenderTarget);
}

void Monster::OnDamage()
{
}

void Monster::Die()
{
	PlayScene::GetGameScene()->OnMonsterDied(this);
	PlayScene::GetGameScene()->SpawnEffect(_pos,"bloodpoof",0,0,EffectAnim::bloodEffect);
	Game::GetInstance()->GetCurrScene()->ReserveRemove(this);
}

void Monster::TakeDamage(float amount)
{

}

void Monster::TakeDamage(float amount, DirType dir)
{
	float speed = 20.f;
	Vector dirvalue = dirValue[dir];
	Vector pos = _pos;
	pos += dirvalue * speed;
	SetPos(pos);

	_attacedTime = now + 0.1f;
	_hp -= amount;
	OnDamage();
	if (_hp <= 0)
	{
		Die();
	}
}
