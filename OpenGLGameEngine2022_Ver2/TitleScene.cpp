#include "Engine.h"
#include "AudioManager.h"
#include "TitleScene.h"
#include "TextureManager.h"
#include "SceneManager.h"

void TitleScene::Init()
{
	__super::Init();

	AudioManager::GetInstance()->LoadAudio("Resources/TitleBgm.mp3", true, DEMO_BGM_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/ButtonClick.mp3", false, DEMO_SFX_INDEX);
	AudioManager::GetInstance()->PlayBGM(DEMO_BGM_INDEX);
	AudioManager::GetInstance()->setVolume(0.2);

	box = new GameObject("TitleSceneBG.png");
	box->SetPosition(350, 450);
	box->SetZOrder(-0.5f);

	startBtn = new GameObject("StartBtn.png");
	startBtn->SetPosition(350, 150);

	/*for (int i = 0; i < 8; i++) {
		string s = "Run (" + to_string(i + 1) + ").png";
		box->AddFrame(s.c_str());
	}
	box->SetPosition(150, 150);
	box->SetScale(0.5, 0.5);
	box->SetRotation(45);
	box->frameRate = 10;*/
}

void TitleScene::Draw()
{
	__super::Draw();

	//glPushMatrix();

	//glTranslated(400, 300, 0);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance()->GetTextureID("ship_1.png"));
	//glBegin(GL_POLYGON);
	//glTexCoord2d(0, 0); glVertex2f(-50, -50);
	//glTexCoord2d(0, 1); glVertex2f(-50, 50);
	//glTexCoord2d(1, 1); glVertex2f(50, 50);
	//glTexCoord2d(1, 0); glVertex2f(50, -50);
	//glEnd();

	//glTranslated(-50, -50, 0);

	//glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance()->GetTextureID("box.png"));
	//glBegin(GL_POLYGON);
	//glTexCoord2d(0, 0); glVertex2f(-50, -50);
	//glTexCoord2d(0, 1); glVertex2f(-50, 50);
	//glTexCoord2d(1, 1); glVertex2f(50, 50);
	//glTexCoord2d(1, 0); glVertex2f(50, -50);
	//glEnd();

	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
}

void TitleScene::Update(float dt)
{
	__super::Update(dt);
}

void TitleScene::KeyDown(string keyCode)
{
	/*if (keyCode == "w") {
		box->py += 10;
	}
	if (keyCode == "a") {
		box->px -= 10;
	}
	if (keyCode == "s") {
		box->py -= 10;
	}
	if (keyCode == "d") {
		box->px += 10;
	}*/

	//cout << keyCode << endl;
	if (keyCode == " ") {
		AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);
		SceneManager::GetInstance()->LoadScene("HowtoplayScene");
	}
}

void TitleScene::MouseOnClick(int button, int state, int x, int y)
{
	if (startBtn->CheckClicked(x, y)) {
		cout << "clicked" << endl;
		AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);
		SceneManager::GetInstance()->LoadScene("HowtoplayScene");
	} 
}

void TitleScene::MouseMove(int x, int y)
{
}

