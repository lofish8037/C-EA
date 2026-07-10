#include "Engine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
    if (instance == nullptr) {
        instance = new SceneManager();
    }
    return instance;
}

SceneManager::SceneManager()
{
    curScene = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Draw()
{
    if (curScene != nullptr) {
        curScene->Draw();
    }
}

void SceneManager::Update(float dt)
{
    if (curScene != nullptr) {
        curScene->Update(dt);
    }
}

void SceneManager::KeyDown(string keyCode)
{
    curScene->KeyDown(keyCode);
}

void SceneManager::MouseOnClick(int button, int state, int x, int y)
{
    curScene->MouseOnClick(button, state, x, y);
}

void SceneManager::MouseMove(int x, int y)
{
    curScene->MouseMove(x, y);
}

Scene* SceneManager::CreateScene(string sceneName)
{
    Scene* tmpScene = nullptr;
    //create other scenes here
    if (sceneName == "TitleScene") { tmpScene = new TitleScene(); }
    if (sceneName == "GameScene") { tmpScene = new GameScene(); }

    if (tmpScene != nullptr)
    {
        tmpScene->sceneName = sceneName;
    }

    return tmpScene;
}

void SceneManager::LoadScene(string sceneName)
{
    Scene* nextScene = CreateScene(sceneName);
    if (curScene) {
        delete(curScene);
    }
    if (nextScene == nullptr) {
        cout << "Create scene fail : " << sceneName << endl;
        return;
    }
    curScene = nextScene;
    curScene->Init();
}

Scene* SceneManager::GetCurrectScene()
{
    return curScene;
}
