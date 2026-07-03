#include "GameObject.h"
#include "SceneManager.h"
#include "TextureManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

GameObject::GameObject()
{
	init();
}

GameObject::GameObject(const char* fileName)
{
	init();
	AddFrame(fileName);
}

GameObject::~GameObject()
{
	delete sprites;
	SceneManager::GetInstance()->GetCurrectScene()->RemoveGameObject(this);
}

void GameObject::init()
{
	name = "";
	px = 0;
	py = 0;
	pz = 0;
	rotation = 0;
	sx = 1;
	sy = 1;

	sprites = new vector<int>();
	curFrame = 0;
	frameRate = 10;
	w = 0;
	h = 0;
	frameTimer = 0;

	SceneManager::GetInstance()->GetCurrectScene()->AddGameObject(this);
}

void GameObject::SetPosition(float _px, float _py)
{
	px = _px;
	py = _py;
}

void GameObject::SetScale(float _sx, float _sy)
{
	sx = _sx;
	sy = _sy;
}

void GameObject::SetRotation(float r)
{
	rotation = r;
}

void GameObject::SetZOrder(float z)
{
	pz = z;
}

void GameObject::Update(float dt)
{
	frameTimer += dt;
	if (frameTimer >= (1.0f / frameRate)) {
		curFrame = (curFrame + 1) % sprites->size();
		frameTimer = 0;
	}
}

void GameObject::Draw()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, sprites->at(curFrame));
	glTranslatef(px, py, pz);
	glRotatef(rotation, 0, 0, 1);
	glScalef(sx, sy, 1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex2f(-w * 0.5, -h * 0.5);
	glTexCoord2d(0, 1); glVertex2f(-w * 0.5, h * 0.5);
	glTexCoord2d(1, 1); glVertex2f(w * 0.5, h * 0.5);
	glTexCoord2d(1, 0); glVertex2f(w * 0.5, -h * 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void GameObject::AddFrame(const char* filename)
{
	TextureInfo info = TextureManager::GetInstance()->GetTextureInfo(filename);
	w = info.width;
	h = info.height;
	sprites->push_back(info.textureID);
}

bool GameObject::CheckClicked(int c_x, int c_y)
{
	int _x = (c_x - px) * cosf(rotation * M_PI / 180.0) + (c_y - py) * sinf(rotation * M_PI / 180.0);
	int _y = (c_x - px) * sinf(rotation * M_PI / 180.0) * -1 + (c_y - py) * cosf(rotation * M_PI / 180.0);
	return (abs(_x) <= w * sx * 0.5f && abs(_y) <= h * sy * 0.5f);
}




