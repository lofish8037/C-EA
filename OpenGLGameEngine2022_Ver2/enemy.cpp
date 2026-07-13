#include "Enemy.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"
#include "TextureManager.h"


Enemy::Enemy(EnemyType type)
{
	px = 350;
	py = 450;
	pz = 0.6;
	IsDead = false;
	waitsprites = new vector<int>();
	attsprites = new vector<int>();

	curanim = Wait;

	switch (type) {
	case 0 :
		CD = 15;
		maxhp = 800;
		maxshield = 0;
		AddFrame("WaitA1.png");
		AddwaitFrame("WaitA1.png");
		AddwaitFrame("WaitA2.png");
		AddwaitFrame("WaitA3.png");
		AddattFrame("AtkA1.png");
		AddattFrame("AtkA2.png");
		AddattFrame("AtkA3.png");
		break;

	case 1:
		CD = 15;
		maxhp = 800;
		maxshield = 50;
		AddFrame("WaitB1.png");
		AddwaitFrame("WaitB1.png");
		AddwaitFrame("WaitB2.png");
		AddwaitFrame("WaitB3.png");
		AddattFrame("AtkB1.png");
		AddattFrame("AtkB2.png");
		AddattFrame("AtkB3.png");
		break;

	case 2:
		CD = 5;
		maxhp = 800;
		maxshield = 100;
		AddFrame("WaitC1.png");
		AddwaitFrame("WaitC1.png");
		AddwaitFrame("WaitC2.png");
		AddwaitFrame("WaitC3.png");
		AddattFrame("AtkC1.png");
		AddattFrame("AtkC2.png");
		AddattFrame("AtkC3.png");
		break;
	}
	
	Hp = maxhp;
	Shield = maxshield;
	
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


	float curHP = 460 + (200 * (Hp / maxhp));
	float curSh = 460 + (200 * (Shield / maxshield));
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

	if (Hp < 0) {
		IsDead = true;
	}
}

void Enemy::TakeDamage(int damage)
{
	Hp -= damage;
	cout << Hp << endl;
	
}

void Enemy::AddwaitFrame(const char* filename)
{
	TextureInfo info = TextureManager::GetInstance()->GetTextureInfo(filename);
	w = info.width;
	h = info.height;
	waitsprites->push_back(info.textureID);
}

void Enemy::AddattFrame(const char* filename)
{
	TextureInfo info = TextureManager::GetInstance()->GetTextureInfo(filename);
	w = info.width;
	h = info.height;
	attsprites->push_back(info.textureID);
}

void Enemy::ChangeState(EnemyState anim)
{
	curanim = anim;
	switch (curanim) {
	case 0:
		sprites = waitsprites;
		break;
	case 1:
		sprites = attsprites;
		break;
	}
	
}





