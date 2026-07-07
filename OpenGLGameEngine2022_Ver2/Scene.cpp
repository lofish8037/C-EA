#include "Scene.h"
#include "Engine.h"

Scene::Scene()
{
	gameObjects = new vector<GameObject*>();
}

Scene::~Scene()
{
}

void Scene::Init()
{
}

void Scene::Update(float dt)
{
	for (int i = 0; i < gameObjects->size(); i++) {
		gameObjects->at(i)->Update(dt);
	}
}

void Scene::Draw()
{
	for (int i = 0; i < gameObjects->size(); i++) {
		gameObjects->at(i)->Draw();
	}
}

void Scene::KeyDown(string keyCode)
{
}

void Scene::MouseOnClick(int button, int state, int x, int y)
{
}

void Scene::MouseMove(int x, int y) {

}

void Scene::AddGameObject(GameObject* obj)
{
	gameObjects->push_back(obj);
}

void Scene::RemoveGameObject(GameObject* obj)
{
	vector<GameObject*>::iterator itr = find(gameObjects->begin(), gameObjects->end(), obj);
	if (itr != gameObjects->end()) {
		gameObjects->erase(itr);
	}
}
