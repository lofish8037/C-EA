#pragma once
#include <string>
#include <vector>
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(const char* fileName);
	~GameObject();

public:
	virtual void SetPosition(float _px, float _py);
	virtual void SetZOrder(float z);
	virtual void SetScale(float _sx, float _sy);
	virtual void SetRotation(float r);
	virtual void Draw();
	virtual void Update(float dt);
	void AddFrame(const char* filename);
	bool CheckClicked(int c_x, int c_y);

private:
	void init();

public:
	string name;
	float px, py, pz;
	float sx, sy;
	float rotation;

	vector<int>* sprites;
	float frameRate; //number of frame / second
	float w, h;
	int curFrame;

private:
	float frameTimer;
};

