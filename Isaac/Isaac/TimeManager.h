#pragma once

#include "Singleton.h"

// �ð� ������ ���α׷��� ����ִ��� �����ϰ� �Ѱ��� ����
// 
// 
// �ǽ� : Ÿ�̸� �ý���, ����ٰ� �ڵ� �߰��Ͻø� �ǿ�.
// Ÿ�̸Ӱ� �� �︮��, �ݹ� �ý��� ���.

class TimeManager : public Singleton<TimeManager>
{
	friend Singleton<TimeManager>;
	
private:
	TimeManager() {}

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency = 0;	// CPU Ŭ��
	uint64 _prevCount = 0;

	// ���������Ӱ� ���� ������ ������ �ð� ����
	float _deltaTime = 0.f;

private:

	// �ʴ� �� ����������
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;
};

