#pragma once

//  �츮�� �����ϴ� ���� �����.
constexpr int GWinSizeX = 972;
constexpr int GWinSizeY = 540;
constexpr int GridSize = 54;

// ������ ������ ����ϴ� ��� & �𸮾� �̷��� ���ϴ�.
using int8 = char;					// ���� �����ϴµ� 1bit ¥��
using int16 = short;
using int32 = int;
using int64 = long long;		// �Ź� long long ���� �����Ƽ� int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

float RadianToDegree(float radian);
float DegreeToRadian(float degree);
bool IsInPoint(RECT rect, POINT pos);

// �𸮾󿡼� ������.
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
	RL_UI,	// UI �� ���� ������
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


// vector ���� ((����+ũ��)�� ��Ÿ���� ����)
struct Vector
{
	// ��ǥ
	float x = 0;
	float y = 0;

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	//Vector p1;
	//Vector p2;
	//Vector p3 = Vector(p1.x + p2.x, p1.y + p2.y);
	//Vector p3 = p1 + p2;
	//p1 += p2;	// �̷� ������ �Ҽ� ��������
	//
	//int a = 10;
	//a += 1;

	// ��Ģ���� ����
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
	// ���͸� ������������ ������ �ʴ�...
	// ������ �ȸ��� ������ ���Ǿ�����.


	// ������ ���� ���ϱ�
	// ���� ���캸��, Legnth, LengthSquared (���ʹ� ���� ���̸� �����ϴ� �Լ��� 2����)
	// sqrt(��Ʈ) ������ �������� ��α� ������, �� ��¥ ���̰� �ʿ��� ��찡 �ƴϸ�,
	// LengthSquared (���� ����) ������ ����ϴ°� �� ����.
	float Length()
	{
		return ::sqrt(x * x + y * y);
	}

	// ������ ���� ����
	float LengthSquared()
	{
		return (x * x + y * y);
	}

	// �̰͵� ���Ӹ���ٰ�. �پ��� ������ �ʿ��ϸ� ���⿡ ������ �ϸ� �ǿ�.
	void Normalize()
	{
		// ������ ��ֶ����� �ϴ� ������ ���������.
		// ������ ��ֶ����� ���� �ʰ�, �����ϴ� ������ �߰��� ������� �־��.
		
		// ������ ũ�⸦ ���ؼ�, ũ�⸸ŭ ������ ���ָ� �ȴ�.
		float length = Length();

		// �𸮾� ������ Ǯ ���¼ҽ�. �𸮾� �����ؼ� �����ص� �����ϴ�.
		//length �� 0�̰ų� ��û ������ �ִ�
		if (length < SMALL_NUMBER)
			return;	// ���� ����ȭ���ϰ� ����

		// ����ȭ.
		x /= length;
		y /= length;	
	}

	// ����ȭ�� ����� ����
	Vector GetNormalize()
	{
		Vector normalize = *this;
		normalize.Normalize();
		return normalize;
	}

	// ������ Dot 
	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// radian ������ŭ ȸ����Ű��.
	Vector Rotate(float radian)
	{
		float cosA = ::cosf(radian);
		float sinA = ::sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}

	// ������ Cross
	float Cross(const Vector& other)
	{
		//2D ��, ��Į�󰪸� ��ȯ�� �Ѵ�. 
		// ���� ���Ͱ� �ʿ��Ѱ� �ƴϰ�, ��ȣ�� �Ǵ��ϴ� ��Į���� �ʿ��ϴ�.
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

	// ��ġ�� �������� ���� �ε��� ���� ����ϴ� �Լ�
	static Cell ConvertToCell(Vector pos, int32 gridSize)
	{
		if (pos.x < 0 || pos.y < 0)
			return Cell{ -1, -1 };	// ����ó���� ���� Cell �ε������� -1�� ����

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

	// ���Ǹ� ���ؼ� == �� ������
	bool operator==(const Cell& other) const
	{
		return index_X == other.index_X && index_Y == other.index_Y;
	}

	// '<' ������ ����
	bool operator<(const Cell& other) const
	{
		if (index_X != other.index_X)
			return index_X < other.index_X;
		return index_Y < other.index_Y;
	}
};