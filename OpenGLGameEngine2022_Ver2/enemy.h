#pragma once
#include"GameObject.h"

class enemy:public GameObject
{
public:
	 void SetPosition(float _px, float _py) override;
	 void SetZOrder(float z) override;
	 void SetScale(float _sx, float _sy) override;
	 void SetRotation(float r) override;
	 void Draw() override;
	 void Update(float dt) override;

	 void TakeDamage(int damage);
	 bool IsDead();

public:
	int hp;
	float speed;
	int atteck;


};