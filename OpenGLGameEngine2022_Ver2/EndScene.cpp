#include "EndScene.h"
#include "Engine.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "GameScene.h"

void EndScene::Init()
{
	__super::Init();

	AudioManager::GetInstance()->LoadAudio("Resources/EndBgm.mp3", true, DEMO_EndBgm_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/Fail.mp3", false, DEMO_Fail_INDEX);

	if (GameScene::IsWin) {
		AudioManager::GetInstance()->PlayBGM(DEMO_EndBgm_INDEX);
		Background = new GameObject("EndSceneBG.png");
		Background->SetPosition(350, 450);
		Background->SetZOrder(-0.8f);
	}
	else {
		AudioManager::GetInstance()->PlaySFX(DEMO_Fail_INDEX);
		Background = new GameObject("GameoverPopUp.png");
		Background->SetPosition(350, 450);
		Background->SetZOrder(-0.8f);

		Btn = new GameObject("HomeBtn.png");
		Btn->SetPosition(350, 400);
	}
	
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
	if (keyCode == " ") {
		SceneManager::GetInstance()->LoadScene("TitleScene");
	}
}

void EndScene::MouseOnClick(int button, int state, int x, int y)
{
	if (Btn->CheckClicked(x, y)) {
		SceneManager::GetInstance()->LoadScene("TitleScene");
	}
}




