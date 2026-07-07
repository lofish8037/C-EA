#pragma once
#include "Scene.h"
#include <string>

using namespace std;

class SceneManager
{
public:
	static SceneManager* instance;

public:
	static SceneManager* GetInstance();

public:
	SceneManager();
	~SceneManager();

public:
	void Draw();
	void Update(float dt);
	void KeyDown(string keyCode);
	void MouseOnClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);


	void LoadScene(string sceneName);
	Scene* GetCurrectScene();

private:
	Scene* CreateScene(string Name);

private:
	Scene* curScene;
};

