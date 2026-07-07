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

	//gamelevel
	int totlaEnemies = 0;
	r = 0;
	if (curlv == 1) {
		
		timer = 60;
	}
	if (curlv == 2) {
		timer = 120;
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
	
	timer -= dt;
	if (timer <= 0) {
		IsGameOver = true;
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
			curbubble->dx = (dx / distance) * 300;
			curbubble->dy = (dy / distance) * 300;
			curbubble->Ismoving = true;
		}
		
	}
}

void GameScene::MouseMove(int x, int y)
{

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
	outX = 25 * ((y % 2) + 1) + x * 25 * 2+25;
	outY = (900 - 40) - (25 + y * (25 * sqrt(3)));
}

bool GameScene::IsgridEmpty(int x, int y)
{
	return (grids[y][x] == nullptr);
}




bool GameScene::IsConect(Bubble* bu)
{
	return false;
}

bool GameScene::CheckDisappear()
{
	return false;
}

bool GameScene::Checkfull()
{
	return false;
}
