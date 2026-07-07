#pragma once
#include "Scene.h"
#include "GameObject.h"

class TitleScene : public Scene
{
public:
	void Init() override;
	void Draw() override;
	void Update(float dt) override;
	virtual void KeyDown(string keyCode) override;
	virtual void MouseOnClick(int button, int state, int x, int y) override;
	virtual void MouseMove(int x, int y) override;
public:
	GameObject* box;
	GameObject* startBtn;
};

