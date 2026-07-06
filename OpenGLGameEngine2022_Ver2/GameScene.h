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

	void PlayerMove(int x, int y);
	bool IsgridEmpty(int x, int y);
	bool CheckWin();
	bool Checkfull();


public:
	GameObject* gameboard;
	GameObject* curball;
	int grids[8][13];

	int curlv;
	float timer;
	bool IsGameOver;

};
