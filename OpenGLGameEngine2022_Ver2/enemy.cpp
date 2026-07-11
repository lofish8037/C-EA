#include "Enemy.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

string enemyimg[3] = { "AtkB3-1.png" ,"WaitB1.png" ,"AtkB3-3.png" };

Enemy::Enemy(const char* fileName)
{
	hp = 800;
	px = 350;
	py = 450;
	CD = 10;
	IsDead = false;
	AddFrame(fileName);
}

void Enemy::SetPosition(float _px, float _py)
{
	__super::SetPosition(_px, _py);
}

void Enemy::SetZOrder(float z)
{
	__super::SetZOrder(z);
}

void Enemy::SetScale(float _sx, float _sy)
{
	__super::SetScale(_sx, _sy);
}

void Enemy::SetRotation(float r)
{
	__super::SetRotation(r);
}

void Enemy::Draw()
{
	__super::Draw();
}

void Enemy::Update(float dt)
{
	__super::Update(dt);

}

void Enemy::TakeDamage(int damage)
{
	hp -= damage;
	cout << hp << endl;
	if (hp < 0) {
		IsDead = true;
	}
}





