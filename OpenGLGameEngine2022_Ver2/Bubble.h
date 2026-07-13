#pragma once
#include"GameObject.h"

enum BubbleType
{
	Green = 0,
	Blue = 1,
	Red = 2
};
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

	void ChangeColor();
	void ChangeBlinded(bool isblind);

public:
	float dx, dy;
	int r;
	BubbleType colortype;
	bool Ismoving;
	bool Isfalling;
	bool Isblinded;
	float timer;
};

