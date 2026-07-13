#pragma once
#include"GameObject.h"

enum EnemyType
{
	Slime = 0,
	Coffin = 1,
	Boss = 2
};

enum EnemyState {
	Wait = 0,
	Att = 1
};

class Enemy:public GameObject
{
public:
	Enemy(EnemyType type);

	 void SetPosition(float _px, float _py) override;
	 void SetZOrder(float z) override;
	 void SetScale(float _sx, float _sy) override;
	 void SetRotation(float r) override;
	 void Draw() override;
	 void Update(float dt) override;

	 void TakeDamage(int damage);
	 void AddwaitFrame(const char* filename);
	 void AddattFrame(const char* filename);
	 void ChangeState(EnemyState anim);

public:
	EnemyType etype;
	EnemyState curanim;
	bool IsDead;
	float Hp, maxhp, maxshield, Shield;
	float CD;
	vector<int>* waitsprites;
	vector<int>* attsprites;
	
};