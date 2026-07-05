#pragma once
#include"Scene.h"

class GameScene :public Scene
{
public:
	void Init() override;
	void Draw() override;
	void Update(float dt) override;
	void KeyDown(string keyCode) override;
	void MouseOnClick(int button, int state, int x, int y) override;

public:
	GameObject* gameboard;
	int bubble_r;

};

