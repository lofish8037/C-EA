#include "GameScene.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

void GameScene::Init() {
	__super::Init();
	gameboard = new GameObject("backg.png");
	gameboard->SetPosition(350, 450);
	gameboard->SetZOrder(-0.8f);

	Topgameboard = new GameObject("frame.png");
	Topgameboard->SetPosition(350, 450);
	Topgameboard->SetZOrder(0.8f);

	magicsk = new GameObject("rod.png");
	magicsk->SetZOrder(0.5f);
	magicsk->SetPosition(225, 120);

	pointLine = new GameObject("pointer.png");
	pointLine->SetPosition(225, 200);
	pointLine->SetZOrder(-0.5f);

	deadline = new GameObject("deadline.png");
	deadline->SetPosition(225, 280);
	deadline->SetZOrder(-0.6f);

	//count = (13 % 2 != 0) ? 7 : 8;

	//gamelevel
	int totlaEnemies = 0;
	timer = 0;
	if (curlv == 1) {
		
	
	}
	if (curlv == 2) {

	}

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 8; j++) {
			grids[i][j] = nullptr;
		}
	}
	for (int r = 0; r < 4; r++) {
		int count = (r % 2 != 0) ? 7 : 8;
		for (int c = 0; c < count; c++) {
				Bubble* bubble = new Bubble();
				float px, py;
				GridToPos(r, c, px, py);
				bubble->SetPosition(px, py);
				grids[r][c] = bubble;

				cout << grids[r][c]->colortype;
		}
	}
	
	curbubble = new Bubble();
	curbubble->SetPosition(225, 200);

	
}

void GameScene::Draw()
{
	__super::Draw();
}

void GameScene::Update(float dt)
{
	__super::Update(dt);
	
	timer += dt;

	if (curbubble->Ismoving) {
		if (IsConect(curbubble)) {
			cout << "IsConect" << endl;
			curbubble->Ismoving = false;

			int x, y;
			PosToGrid(curbubble->px, curbubble->py, y, x);
			
			grids[y][x] = curbubble;

			float px, py;
			GridToPos(y, x, px, py);
			curbubble->SetPosition(px, py);

			// Check
			CheckDisappear(y, x);
			for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 8; j++) {
				cout << grids[i][j] << " ";
			}
			cout << endl;
			}

			curbubble = new Bubble();
			curbubble->SetPosition(225, 200);
		}
	}

	
}

void GameScene::KeyDown(string keyCode)
{
	__super::KeyDown(keyCode);

	//if (keyCode == "a"&& r<=45) {
	//	r ++;
	//}
	//else if (keyCode == "d" && r >= -45) {
	//	r --;
	//}
	//pointLine->SetRotation(r);

	//if (keyCode == " " && !curbubble->Ismoving) {
	//	curbubble->SetRotation(r);
	//	curbubble->Ismoving = true;
	//	/*for (int i = 0; i < 13; i++) {       
	//		for (int j = 0; j < 8; j++) {    
	//			cout << grids[i][j] << " ";
	//		}
	//		cout << endl;
	//	}*/
	//}
}

void GameScene::MouseOnClick(int button, int state, int x, int y)
{
	__super::MouseOnClick(button, state, x, y);
	if (!curbubble->Ismoving) {
		float dx = x - curbubble->px;
		float dy = y - curbubble->py;

		if (dy > 0) {
			if (dx > dy) dx = dy;
			if (dx < -dy) dx = -dy;
			float distance = sqrt(dx * dx + dy * dy);
			cout << distance << endl;
			curbubble->dx = (dx / distance) * 500;
			curbubble->dy = (dy / distance) * 500;
			curbubble->Ismoving = true;
		}
		
	}
	
}

void GameScene::MouseMove(int x, int y)
{
	__super::MouseMove(x, y);
	
	angle = atan2(x - pointLine->px, y - pointLine->py) * 180.0f / acos(-1);
	if (angle > 45) angle = 45;
	if (angle < -45) angle = -45;
	
	pointLine->SetRotation(angle*-1);
}

//void GameScene::PlayerMove(int x, int y)
//{
//	if (IsGameOver) {
//		return;
//	}
//
//	if (IsgridEmpty(x, y)) {
//		grids[y][x] = curbubble;
//	}
//
//}

void GameScene::GridToPos(int y, int x, float& outX, float& outY)
{
	outX = 25 * ((y % 2) + 1) + x * 25 * 2 + 25;
	outY = (900 - 40) - (25 + y * (25 * sqrt(3) + 3));
}

void GameScene::PosToGrid(float x, float y, int& outY, int& outX)
{
	outY = round((900 - 40 - y - 25) / (25 * sqrt(3) + 3));
	outX = round((x - (25 * ((outY % 2) + 1) + 25)) / (25 * 2));
}

bool GameScene::IsgridEmpty(int x, int y)
{
	return (grids[y][x] == nullptr);
}




bool GameScene::IsConect(Bubble* bu)
{
	if (bu->py >= 835) {
		return true;
	}
	for (int i = 0; i < 13; i++) {
		int count = (i % 2 != 0) ? 7 : 8;
		for (int j = 0; j < count; j++) {
			if (grids[i][j] != nullptr) {
				float dx = bu->px - grids[i][j]->px;
				float dy = bu->py - grids[i][j]->py;
				float dis = sqrt(dx * dx + dy * dy);
				if (dis <= 50) {
					return true;
				}
			}
		}
	}
	return false;
}

void GameScene::CheckDisappear(int y ,int x)
{
	if (matchedBu == nullptr) {
		matchedBu = new vector<Bubble*>();
	}
	else {
		matchedBu->clear();
	}

	bool checked[13][8] = { false };

	CheckSameType(y, x, grids[y][x]->colortype, checked);

	if (matchedBu->size() >= 3) {
		for (int i = 0; i < matchedBu->size(); i++) {
			RemoveGameObject(matchedBu->at(i));

			for (int r = 0; r < 13; r++) {
				for (int c = 0; c < 8; c++) {
					if (grids[r][c] == matchedBu->at(i)) {grids[r][c] = nullptr;}
					}
				}
			}
		}

	bool checkedempty[13][8] = { false };
	for (int i = 0; i < 8;i++) {
		if (grids[0][i] != nullptr) {
			CheckEmpty(0, i, checkedempty);
		}
	}
	for (int r = 0; r < 13; r++) {
		for (int c = 0; c < 8; c++) {
			if (grids[r][c] != nullptr && !checkedempty[r][c])
			{ 
				grids[r][c]->Isfalling = true;
				grids[r][c] = nullptr;
				
			}
		}
	}

}

void GameScene::CheckSameType(int y, int x, int buType, bool checked[13][8])
{
	if (y < 0 || y >= 13 || x < 0 || x >= 8) return;
	if (grids[y][x] == nullptr) return;
	if (checked[y][x]) return;
	if (grids[y][x]->colortype != buType) return;

	checked[y][x] = true;
	matchedBu->push_back(grids[y][x]);

	int count = (y % 2 != 0) ? x : x - 1;

	CheckSameType(y - 1, count, buType, checked);
	CheckSameType(y - 1, count +1, buType, checked);
	CheckSameType(y, x-1, buType, checked);
	CheckSameType(y, x+1, buType, checked);
	CheckSameType(y + 1, count, buType, checked);
	CheckSameType(y + 1, count+1, buType, checked);
}

void GameScene::CheckEmpty(int y, int x, bool checked[13][8])
{
	if (y < 0 || y >= 13 || x < 0 || x >= 8) return;
	if (grids[y][x] == nullptr) return;
	if (checked[y][x]) return;

	checked[y][x] = true;
	int count = (y % 2 != 0) ? x : x - 1;

	CheckEmpty(y - 1, count, checked);
	CheckEmpty(y - 1, count + 1, checked);
	CheckEmpty(y, x - 1, checked);
	CheckEmpty(y, x + 1, checked);
	CheckEmpty(y + 1, count, checked);
	CheckEmpty(y + 1, count + 1, checked);
}

bool GameScene::Checkfull()
{
	return false;
}
