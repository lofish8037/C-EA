#include "Bubble.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

string ballimg[3] = { "Ball.png" ,"Ball1.png" ,"Ball2.png" };

Bubble::Bubble()
{
	AudioManager::GetInstance()->LoadAudio("Resources/BubbleShoot.mp3", false, DEMO_BubbleShoot_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/BubbleDistory.mp3", false, DEMO_BubbleDistory_INDEX);
	Ismoving = false;
	Isfalling = false;
	timer = 5;
	dx = dy = 0;
	r = 25;
	colortype = BubbleType(rand() % 3);
	AddFrame(ballimg[colortype].c_str());
}

Bubble::~Bubble()
{
}

void Bubble::SetPosition(float _px, float _py)
{
	__super::SetPosition(_px, _py);
}

void Bubble::SetZOrder(float z)
{
	__super::SetZOrder(z);
}

void Bubble::SetScale(float _sx, float _sy)
{
	__super::SetScale(_sx, _sy);
}

void Bubble::SetRotation(float r)
{
	__super::SetRotation(r);
}

void Bubble::Draw()
{
	__super::Draw();

}

void Bubble::Update(float dt)
{
	__super::Update(dt);

	if (Ismoving) {
		py += dt * dy;
		px += dt * dx;
		if (px - r <= 25 || px + r >= 425) {
			dx *= -1;
		}
	}

	if (Isfalling) {
		py -= dt * 500;
	}

	if (Isblinded) {
		timer -= dt;
		if (timer <= 0) {
			ChangeBlinded(false);
		}
	}
	

}

void Bubble::ChangeColor()
{
	colortype = BubbleType(rand() % 3);
	sprites->clear();
	AddFrame(ballimg[colortype].c_str());
}

void Bubble::ChangeBlinded(bool isblind)
{
	sprites->clear();
	if (isblind) {
		Isblinded = true;
		timer = 5;
		AddFrame("BadBall.png");
	}
	else {
		Isblinded = false;
		AddFrame(ballimg[colortype].c_str());
	}
}
