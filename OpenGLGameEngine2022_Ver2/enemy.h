#pragma once
#include"GameObject.h"


class enemy:public GameObject
{
public:
	enemy(const char* fileName);


	 void SetPosition(float _px, float _py) override;
	 void SetZOrder(float z) override;
	 void SetScale(float _sx, float _sy) override;
	 void SetRotation(float r) override;
	 void Draw() override;
	 void Update(float dt) override;

	 void TakeDamage(int damage);
	 bool Addrow(int count);

public:
	bool IsDead;
	int hp;
	int CD;

};