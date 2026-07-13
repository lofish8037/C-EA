#include "EndScene.h"
#include "Engine.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

void EndScene::Init()
{
	__super::Init();
	Background = new GameObject("GameoverPopUp.png");
	Background->SetPosition(350, 450);
	Background->SetZOrder(-0.8f);

	Btn = new GameObject("HomeBtn.png");
	Btn->SetPosition(405, 400);
}

void EndScene::Draw()
{
	__super::Draw();
}

void EndScene::Update(float dt)
{
	__super::Update(dt);
}

void EndScene::KeyDown(string keyCode)
{
}

void EndScene::MouseOnClick(int button, int state, int x, int y)
{
	if (Btn->CheckClicked(x, y)) {
		SceneManager::GetInstance()->LoadScene("TitleScene");

	}
}

void EndScene::MouseMove(int x, int y)
{
}


