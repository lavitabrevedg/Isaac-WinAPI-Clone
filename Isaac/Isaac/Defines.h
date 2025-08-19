#pragma once

//  우리가 정의하는 공용 선언들.
constexpr int GWinSizeX = 972;
constexpr int GWinSizeY = 540;
constexpr int GridSize = 54;

// 엔씨에 있을때 사용하던 방식 & 언리얼도 이렇게 씁니다.
using int8 = char;					// 정수 저장하는데 1bit 짜리
using int16 = short;
using int32 = int;
using int64 = long long;		// 매번 long long 쓰기 귀찮아서 int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

float RadianToDegree(float radian);
float DegreeToRadian(float degree);
bool IsInPoint(RECT rect, POINT pos);

// 언리얼에서 가져옴.
#define SMALL_NUMBER			(1.e-8f)

const float PI = 3.1415926f;

#define SAFE_RELEASE(p) if(p) { p->Release(); p = nullptr; }
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

enum BrushColor
{
	Red,
	White,
	Blue,
};

enum FontSize
{
	FONT_12 = 12,
	FONT_16 = 16,
	FONT_20 = 20,
	FONT_30 = 30,
};

struct RectangleXY
{
	float    left;
	float    top;
	float    right;
	float    bottom;
};

struct Dimension
{
	int32 Width = 0;
	int32 Height = 0;
};


struct AnimInfo
{
	int32 startX = 0;
	int32 startY = 0;
	int32 countX = 0;
	int32 countY = 0;
	bool loop = false;
	float duration = 0.2f;
	bool flipX = false;
};

struct SpriteInfo
{
	int32 indexX = 0;
	int32 indexY = 0;
	string bitmapKey;
	bool alignCenter = true;
};

enum RenderLayer
{
	RL_Room,
	RL_Item,
	RL_Object,
	RL_Monster,
	RL_Player,
	RL_Effect,
	RL_Tear,
	RL_UI,	// UI 는 제일 마지막
	RL_Image,
	RL_Count
};

enum DirType
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_MAX,
};


// vector 구현 ((방향+크기)를 나타내는 벡터)
struct Vector
{
	// 좌표
	float x = 0;
	float y = 0;

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	//Vector p1;
	//Vector p2;
	//Vector p3 = Vector(p1.x + p2.x, p1.y + p2.y);
	//Vector p3 = p1 + p2;
	//p1 += p2;	// 이런 덧셈도 할수 있을지도
	//
	//int a = 10;
	//a += 1;

	// 사칙연산 정의
	// +, - , *, / 
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	Vector operator*(float ratio)
	{
		Vector ret;
		ret.x = x * ratio;
		ret.y = y * ratio;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}
	bool operator==(const Vector& other) const
	{
		return (x == other.x && y == other.y);
	}
	// 벡터를 나눗셈할일이 많지가 않다...
	// 연산자 안만들어도 쓸일이 거의없을듯.


	// 벡터의 길이 구하기
	// 엔진 살펴보면, Legnth, LengthSquared (벡터는 보통 길이를 리턴하는 함수가 2종류)
	// sqrt(루트) 연산은 생각보다 비싸기 때문에, 꼭 진짜 길이가 필요한 경우가 아니면,
	// LengthSquared (제곱 길이) 버전을 사용하는게 더 좋다.
	float Length()
	{
		return ::sqrt(x * x + y * y);
	}

	// 길이의 제곱 버전
	float LengthSquared()
	{
		return (x * x + y * y);
	}

	// 이것도 게임만들다가. 다양한 버전이 필요하면 여기에 재정의 하면 되요.
	void Normalize()
	{
		// 스스로 노멀라이즈 하는 버전만 만들거지만.
		// 스스로 노멀라이즈 하지 않고, 리턴하는 버전을 추가로 만들수도 있어요.
		
		// 벡터의 크기를 구해서, 크기만큼 나누기 해주면 된다.
		float length = Length();

		// 언리얼 엔진은 풀 오픈소스. 언리얼 참고해서 공부해도 좋습니다.
		//length 가 0이거나 엄청 작을수 있다
		if (length < SMALL_NUMBER)
			return;	// 굳이 정규화안하고 리턴

		// 정규화.
		x /= length;
		y /= length;	
	}

	// 정규화된 복사된 벡터
	Vector GetNormalize()
	{
		Vector normalize = *this;
		normalize.Normalize();
		return normalize;
	}

	// 내적은 Dot 
	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// radian 각도만큼 회전시키자.
	Vector Rotate(float radian)
	{
		float cosA = ::cosf(radian);
		float sinA = ::sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}

	// 외적은 Cross
	float Cross(const Vector& other)
	{
		//2D 라서, 스칼라값만 반환을 한다. 
		// 법선 벡터가 필요한게 아니고, 부호를 판단하는 스칼라값이 필요하다.
		return x * other.y - y * other.x;
	}
};

struct CellInfo
{
	set<class Actor*> _actorsInCell;
	bool canMoveCell = true;
};

struct Cell
{
	int32 index_X;
	int32 index_Y;

	// 위치를 기준으로 셀의 인덱스 값을 계산하는 함수
	static Cell ConvertToCell(Vector pos, int32 gridSize)
	{
		if (pos.x < 0 || pos.y < 0)
			return Cell{ -1, -1 };	// 예외처리를 위한 Cell 인덱스값을 -1로 정의

		if (pos.x > GWinSizeX || pos.y > GWinSizeY)
			return Cell{ -1,-1 };

		return Cell{ (int32)(pos.x / gridSize), (int32)(pos.y / gridSize) };
	}

	static Vector ConvertToWorld(Cell cell, int32 gridSize)
	{
		if (cell.index_X < 0 || cell.index_Y < 0)
			return Vector{ -1,-1 };

		return Vector{ (float)(cell.index_X * GridSize + (GridSize * 0.5f)),(float)(cell.index_Y * GridSize + (GridSize * 0.5f)) };
	}

	// 편의를 위해서 == 비교 연산자
	bool operator==(const Cell& other) const
	{
		return index_X == other.index_X && index_Y == other.index_Y;
	}

	// '<' 연산자 정의
	bool operator<(const Cell& other) const
	{
		if (index_X != other.index_X)
			return index_X < other.index_X;
		return index_Y < other.index_Y;
	}
};