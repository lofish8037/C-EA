#pragma once
#include"GameObject.h"


class Enemy:public GameObject
{
public:
	Enemy(const char* fileName);


	 void SetPosition(float _px, float _py) override;
	 void SetZOrder(float z) override;
	 void SetScale(float _sx, float _sy) override;
	 void SetRotation(float r) override;
	 void Draw() override;
	 void Update(float dt) override;

	 void TakeDamage(int damage);

public:
	bool IsDead;
	int hp;
	float CD;

};