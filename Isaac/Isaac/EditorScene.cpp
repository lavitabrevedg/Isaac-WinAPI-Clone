#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Game.h"
#include "StageLoader.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Tile.h"
#include "Block.h"
#include "Door.h"


void EditorScene::Init()
{
	Super::Init();

	InputManager::GetInstance()->SetEventMouseWheel([this](int32 delta)
		{
			OnMouseWheel(delta);
		});

	{
		SELECT_MODE mode = SELECT_MODE::ROOM;

		Actor* well7 = new Tile("Well7",GridSize * 7,GridSize * 3);
		well7->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well7);
		Actor* guid = new Tile("Guid",0,0);
		guid->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(guid);

		/*Actor* door = new Door("Door", 0, 0);
		door->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(door);*/
	}

	{
		SELECT_MODE mode = SELECT_MODE::OBJECT;

		Actor* rock = new Block("rock",54,54);
		rock->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(rock);
		Actor* well4 = new Block("Well4", 0, 0);
		well4->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well4);
		Actor* well2 = new Block("Well2", 0, 0);
		well2->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well2);
		Actor* well3 = new Block("Well3", 0, 0);
		well3->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well3);
		Actor* well8 = new Block("Well8", 0, 0);
		well8->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well8);
		Actor* well9 = new Block("Well9", 0, 0);
		well9->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well9);

		Actor* well = new Block("Well", 0, 0);
		well->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well);

		Actor* well5 = new Block("Well5", 0, 0);
		well5->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well5);

		Actor* well6 = new Block("Well6", 0, 0);
		well6->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(well6);
	}

	{
		SELECT_MODE mode = SELECT_MODE::MONSTER;

		Actor* gaper = new Monster();
		gaper->Init(Vector(0, 0));

		_editActorInfo[(int32)mode].push_back(gaper);
	}
}

void EditorScene::Destroy()
{
	InputManager::GetInstance()->SetEventMouseWheel(nullptr);
	Super::Destroy();

	for (auto info : _editActorInfo)
	{
		for (auto iter : info)
		{
			iter->Destroy();
			SAFE_DELETE(iter);
		}
	}
}

void EditorScene::Update(float deltatime)
{
	if (InputManager::GetInstance()->GetButtonDown(KeyType::F1))
	{
		_Actorindex = 0;
		_currMode = SELECT_MODE::ROOM;
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::F2))
	{
		_Actorindex = 0;
		_currMode = SELECT_MODE::OBJECT;
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::F3))
	{
		_Actorindex = 0;
		_currMode = SELECT_MODE::MONSTER;
	}
	//else if (InputManager::GetInstance()->GetButtonDown(KeyType::E))
	//{
	//	_rotateIndex++;
	//	if (_rotateIndex == DirType::DIR_MAX) { _rotateIndex = 0; }
	//	_editActorInfo[(int32)_currMode][_Actorindex]->GetSprite()->SetRotate(_dir[_rotateIndex]); 방향바꾸기
	//}
	//else if (InputManager::GetInstance()->GetButtonDown(KeyType::Q))
	//{
	//	_rotateIndex++;
	//	if (_rotateIndex == DirType::DIR_MAX) { _rotateIndex = 0; }
	//	_editActorInfo[(int32)_currMode][_Actorindex]->GetSprite()->SetRotate(-_dir[_rotateIndex]);
	//}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::LeftMouse))
	{
		POINT mousePos = InputManager::GetInstance()->GetMousePos();
		float x = (float)mousePos.x;
		float y = (float)mousePos.y;
		
		Actor* newActor = nullptr;
		if (_currMode == SELECT_MODE::ROOM)
		{
			Cell mouseCellPos = Cell::ConvertToCell(Vector(x,y), GridSize);
			Vector pos = mouseCellPos.ConvertToWorld(mouseCellPos,GridSize);

			Actor* mouseActor = _editActorInfo[(int32)_currMode][_Actorindex];
			Sprite* copy = mouseActor->GetSprite();
			newActor = new Tile(copy);
			newActor->Init(pos);
		}
		else if (_currMode == SELECT_MODE::OBJECT)
		{
			Cell mouseCellPos = Cell::ConvertToCell(Vector(x, y), GridSize);
			Vector pos = mouseCellPos.ConvertToWorld(mouseCellPos, GridSize);

			Actor* mouseActor = _editActorInfo[(int32)_currMode][_Actorindex];
			Sprite* copy = mouseActor->GetSprite();
			newActor = new Block(copy);
			newActor->Init(pos);
		}
		else if (_currMode == SELECT_MODE::MONSTER)
		{
			Actor* mouseActor = _editActorInfo[(int32)_currMode][_Actorindex];
			Sprite* copy = mouseActor->GetSprite();
			newActor = new Monster();
			newActor->Init(Vector{x,y});
		}

		AddActor(newActor);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::S))
	{
		Save();
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::L))
	{
		Load();
	}
	//else if (InputManager::GetInstance()->GetButtonDown(KeyType::RightMouse))
	//{
	//	POINT mousePos = InputManager::GetInstance()->GetMousePos();
	//	float x = mousePos.x;
	//	float y = mousePos.y;

	//	Cell cell = Cell::ConvertToCell(Vector(x, y),GridSize);

	//	if(cell == )
	//}

}

void EditorScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);

	POINT mousePos = InputManager::GetInstance()->GetMousePos();

	_editActorInfo[(int32)_currMode][_Actorindex]->SetPos(Vector((float)mousePos.x, (float)mousePos.y));
	_editActorInfo[(int32)_currMode][_Actorindex]->Render(_dxRenderTarget);
}

void EditorScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("Guid", L"Room/Guid.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Tile", L"Room/Tile.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well", L"Room/Well.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well2", L"Room/Well2.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well3", L"Room/Well3.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well4", L"Room/Well4.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well5", L"Room/Well5.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well6", L"Room/Well6.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well7", L"Room/Well7.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well8", L"Room/Well8.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well9", L"Room/Well9.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Door", L"Room/Door.png", 2, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Combat", L"Monster/Combat.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Fly", L"Monster/Fly.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Fly2", L"Monster/Fly2.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Monstro", L"Monster/Monstro.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("gaperHead", L"Monster/gaperHead.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("gaperBody", L"Monster/gaperBody.png", 10, 2);

	ResourceManager::GetInstance()->LoadDXBitmap("Bomb", L"Items/Bomb.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Chest", L"Items/Chest.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Heart", L"Items/Heart.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Key", L"Items/Key.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Penny1", L"Items/Penny1.png", 1, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("rock", L"Object/rock.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("rocks", L"Object/rocks.png", 1, 1);
}

void EditorScene::createObjects()
{
}

void EditorScene::createUI()
{
}

void EditorScene::initTimer()
{
}

void EditorScene::Save()
{
	OPENFILENAME ofn;
	wchar_t szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Game::GetInstance()->GetHwnd();
	ofn.lpstrFilter = L"스테이지 파일 (*.stage)\0*.stage\0모든 파일 (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"room";

	//// 파일 이름이 선택되었으면 저장
	if (GetSaveFileName(&ofn))
	{
		std::wstring fileName = szFileName;

		std::wofstream file(fileName);
		if (file.is_open())
		{
			for (auto iter : _actors)
			{
				iter->SaveActor(file);
			}

			file.close();
		}
	}
}

void EditorScene::Load()
{
	// 파일 열기 윈도우창 생성
	OPENFILENAME ofn;
	wchar_t szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Game::GetInstance()->GetHwnd();
	ofn.lpstrFilter = L"스테이지 파일 (*.stage)\0*.stage\0모든 파일 (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"room";

	if (GetOpenFileName(&ofn))
	{
		// 파일 이름이 선택되었으면 로드
		std::wstring fileName = szFileName;

		std::wifstream file(fileName);
		if (file.is_open())
		{
			StageLoader loader;
			loader.Load(this, file);

			file.close();
			MessageBox(Game::GetInstance()->GetHwnd(), L"맵이 로드되었습니다.", L"로드 완료", MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBox(Game::GetInstance()->GetHwnd(), L"파일을 로드할 수 없습니다.", L"오류", MB_OK | MB_ICONERROR);
		}
	}
}

void EditorScene::OnMouseWheel(int32 delta)
{
	_Actorindex++;
	
	if (_Actorindex == _editActorInfo[(int32)_currMode].size())
	{
		_Actorindex = 0;
	}
}