#pragma once
#include "GameObject.h"
#include <vector>
#include <string>

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void KeyDown(string keyCode);
	virtual void MouseOnClick(int button, int state, int x, int y);
	virtual void MouseMove(int x, int y);
	void AddGameObject(GameObject* obj);
	void RemoveGameObject(GameObject* obj);
public:
	string sceneName;

private:
	vector<GameObject*>* gameObjects;
};

