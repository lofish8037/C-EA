#include "Effect.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"


void Effect::Update(float dt)
{
	__super::Update(dt);
	if (curFrame == sprites->size() - 1) {
		delete this;
	}
}

Effect::Effect(float x, float y)
{
	SetPosition(x, y);
	SetZOrder(0.4);

	AddFrame("Disappear1.png");
	AddFrame("Disappear2.png");
	AddFrame("Disappear3.png");
	AddFrame("Disappear4.png");
	AddFrame("Disappear5.png");
}

