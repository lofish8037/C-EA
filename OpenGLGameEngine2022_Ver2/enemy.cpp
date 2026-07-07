#include "enemy.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"


enemy::enemy(const char* fileName)
{
	hp = 10;
	CD = 6;
	IsDead = false;
	AddFrame(fileName);
}

void enemy::SetPosition(float _px, float _py)
{
	__super::SetPosition(_px, _py);
}

void enemy::SetZOrder(float z)
{
	__super::SetZOrder(z);
}

void enemy::SetScale(float _sx, float _sy)
{
	__super::SetScale(_sx, _sy);
}

void enemy::SetRotation(float r)
{
	__super::SetRotation(r);
}

void enemy::Draw()
{
	__super::Draw();
}

void enemy::Update(float dt)
{
	__super::Update(dt);

}

void enemy::TakeDamage(int damage)
{
	hp -= damage;
	if (hp < 0) {
		IsDead = true;
	}
}

bool enemy::Addrow(int count)
{
	if (count == CD) {
		return true;
	}

	return false;
}



