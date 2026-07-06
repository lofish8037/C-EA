#include "GameScene.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

void GameScene::Init() {
	__super::Init();
	gameboard = new GameObject("Background.png");
	gameboard->SetPosition(350, 450);
	gameboard->SetZOrder(-0.5f);

	//gamelevel
	int totlaEnemies = 0;
	if (curlv == 1) {

	}
}

void GameScene::Draw()
{
	__super::Draw();
}

void GameScene::Update(float dt)
{
	__super::Update(dt);
}

void GameScene::KeyDown(string keyCode)
{
	__super::KeyDown(keyCode);

}

void GameScene::MouseOnClick(int button, int state, int x, int y)
{
	__super::MouseOnClick(button, state, x, y);

}

void GameScene::PlayerMove(int x, int y)
{
}

bool GameScene::IsgridEmpty(int x, int y)
{
	return false;
}

bool GameScene::CheckWin()
{
	return false;
}

bool GameScene::Checkfull()
{
	return false;
}
