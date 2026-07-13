#include "HowtoplayScene.h"
#include "Engine.h"
#include "AudioManager.h"
#include "SceneManager.h"


void HowtoplayScene::Init()
{
	__super::Init();
	AudioManager::GetInstance()->LoadAudio("Resources/TitleBgm.mp3", true, DEMO_BGM_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/ButtonClick.mp3", false, DEMO_SFX_INDEX);
	AudioManager::GetInstance()->PlayBGM(DEMO_BGM_INDEX);
	AudioManager::GetInstance()->setVolume(0.2);

	count = 0;

	HTPbackground = new GameObject("HowToPlay1.png");
	HTPbackground->SetPosition(350, 450);
	HTPbackground->SetZOrder(-0.1);

	NextBtn = new GameObject("NextBtn.png");
	NextBtn->SetPosition(350, 75);
}

void HowtoplayScene::Update(float dt)
{
}

void HowtoplayScene::KeyDown(string keyCode)
{

}

void HowtoplayScene::MouseOnClick(int button, int state, int x, int y)
{
	AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);

	if (count == 0 && NextBtn->CheckClicked(x, y)) {
		count ++;
		HTPbackground->sprites->clear();
		NextBtn->sprites->clear();
		NextBtn->AddFrame("GoBtn.png");
		HTPbackground->AddFrame("HowToPlay2.png");
	}
	else if (count == 1 && NextBtn->CheckClicked(x, y)) {
		count = 0;
		SceneManager::GetInstance()->LoadScene("GameScene");
	}

}
