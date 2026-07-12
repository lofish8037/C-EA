#include "Bubble.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

string ballimg[3] = { "Ball.png" ,"Ball1.png" ,"Ball2.png" };

Bubble::Bubble()
{
	Ismoving = false;
	Isfalling = false;

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
		AddFrame("BadBall.png");
	}
	else {
		AddFrame(ballimg[colortype].c_str());
	}
}
