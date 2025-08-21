#pragma once

class StageLoader
{
public:
	// 반환값은 스테이지에서 클리어해야하는 Star 의 개수
	bool Load(class Scene* scene, std::wifstream& file);
	//void unLoad(class Scene* scene);
};

