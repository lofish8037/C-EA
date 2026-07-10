#pragma once
#include"GameObject.h"

class Bubble :public GameObject
{
public:
	Bubble();
	~Bubble();

public:
	void SetPosition(float _px, float _py) override;
	void SetZOrder(float z) override;
	void SetScale(float _sx, float _sy) override;
	void SetRotation(float r) override;
	void Draw() override;
	void Update(float dt) override;

public:
	float dx, dy;
	int r;
	int colortype;
	bool Ismoving;
	bool Isfalling;

};

