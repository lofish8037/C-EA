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
	void MouseMove(int x, int y) override;

	//void PlayerMove(int x, int y);
	void GridToPos(int x, int y, float& outX, float& outY);
	void PosToGrid(float x, float y, int& outx, int& outy);
	bool IsgridEmpty(int x, int y);
	void AddBubble();
	
	bool IsConect(Bubble* bu);
	void CheckDisappear(int y, int x);
	void CheckSameType(int y, int x, BubbleType buType, bool checked[13][8]);
	void CheckEmpty(int y, int x, bool checked[13][8]);



public:
	GameObject* gameboard;
	GameObject* Topgameboard;
	GameObject* pointLine;
	GameObject* magicsk;
	GameObject* deadline;
	GameObject* SkillUI;
	GameObject* LevelUI;

	GameObject* stopBtn;
	GameObject* popupUI;
	GameObject* restartB;
	GameObject* homeB;

	Bubble* curbubble;
	Enemy* Slime;
	vector<Enemy*>* enemies;
	Bubble* grids[13][8];
	vector<Bubble*>* matchedBu;


	float timer;
	int dropCount;
	int blueCount, greenCount, redCount;
	bool IsGameOver, IsPaused;
	float angle;
};