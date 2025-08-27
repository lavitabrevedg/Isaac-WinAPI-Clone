#pragma once
class Stat
{
	struct ItemStat
	{
		float damageAdd = 0.f;
		float damageMul = 1.f;
		float tearsAdd = 0.f;
		float tearsMul = 1.f;
		float shotspeedAdd = 0.f;
		float shotspeedMul = 1.f;
	};

	struct TearStat
	{
		float damage;
		float tears;
		float range;
		float shot_speed;
	};

};

