#pragma once
#include"GameObject.h"

class Effect :public GameObject
{
public:
	void Update(float dt) override;
	Effect(float x, float y);

};

