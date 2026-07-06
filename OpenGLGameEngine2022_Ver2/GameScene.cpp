#include "GameScene.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

void GameScene::Init() {
	__super::Init();
	gameboard = new GameObject("Background.png");
	gameboard->SetPosition(350, 450);
	gameboard->SetZOrder(-0.5f);
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
