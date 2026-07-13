#pragma once
#include "Scene.h"

class HowtoplayScene : public Scene
{
public:
	void Init() override;
	void Update(float dt) override;
	virtual void KeyDown(string keyCode) override;
	virtual void MouseOnClick(int button, int state, int x, int y) override;

public:
	GameObject* HTPbackground;
	GameObject* NextBtn;
	int count;
};

