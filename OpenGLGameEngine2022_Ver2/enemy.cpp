#include "Enemy.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

string enemyimg[3] = { "AtkB3-1.png" ,"enemy1.png" ,"enemy1.png" };

Enemy::Enemy(const char* fileName)
{
	maxhp = 800;
	hp = maxhp;
	shield = 0;
	px = 350;
	py = 450;
	pz = 0.6;
	CD = 15;
	BossCD = 5;
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

	float curHP = 460 + (200 * (hp / maxhp));

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(460, 325, 0.4);
	glVertex3f(460, 310, 0.4);
	glVertex3f(curHP, 310, 0.4);
	glVertex3f(curHP, 325, 0.4);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

}

void Enemy::Update(float dt)
{
	__super::Update(dt);

	if (hp < 0) {
		IsDead = true;
	}
}

void Enemy::TakeDamage(int damage)
{
	hp -= damage;
	cout << hp << endl;
	
}





