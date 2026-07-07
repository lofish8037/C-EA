#pragma once
#include"Scene.h"
#include"enemy.h"
#include "Bubble.h"

class GameScene :public Scene
{
public:
	void Init() override;
	void Draw() override;
	void Update(float dt) override;
	void KeyDown(string keyCode) override;
	void MouseOnClick(int button, int state, int x, int y) override;
	virtual void MouseMove(int x, int y) override;

	//void PlayerMove(int x, int y);
	void GridToPos(int x, int y, float& outX, float& outY);
	bool IsgridEmpty(int x, int y);

	
	bool IsConect(Bubble* bu);
	bool CheckDisappear();
	bool Checkfull();


public:
	GameObject* gameboard;
	GameObject* Topgameboard;
	GameObject* pointLine;
	GameObject* magicsk;

	Bubble* curbubble;
	enemy* enemise;
	Bubble* grids[13][8];

	int curlv;

	float timer;
	bool IsGameOver;
	float r;
};
