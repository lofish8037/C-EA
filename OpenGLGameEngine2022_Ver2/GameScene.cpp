#include "GameScene.h"
#include "Engine.h"
#include "SceneManager.h"
#include"AudioManager.h"

string Lvimg[3] = { "LevelBar.png" ,"Level2Bar.png" ,"Level3Bar.png" };
bool GameScene::IsWin = false;

void GameScene::Init() {
	__super::Init();
	gameboard = new GameObject("backg.png");
	gameboard->SetPosition(350, 450);
	gameboard->SetZOrder(-0.8f);

	Topgameboard = new GameObject("frame.png");
	Topgameboard->SetPosition(350, 450);
	Topgameboard->SetZOrder(0.2f);

	magicsk = new GameObject("rod.png");
	magicsk->SetPosition(225, 200);

	pointLine = new GameObject("pointer.png");
	pointLine->SetPosition(225, 200);
	pointLine->SetZOrder(-0.6f);

	deadline = new GameObject("deadline.png");
	deadline->SetPosition(225, 280);
	deadline->SetZOrder(-0.5f);

	stopBtn = new GameObject("PauseBtn.png");
	stopBtn->SetPosition(560, 865);
	stopBtn->SetZOrder(0.5f);

	SkillUI = new GameObject("SkillsBoard.png");
	SkillUI->SetPosition(350, 450);
	SkillUI->SetZOrder(0.5f);

	LevelUI = new GameObject(Lvimg[enemyCount].c_str());
	LevelUI->SetPosition(350, 450);
	LevelUI->SetZOrder(0.5f);

	popupUI = new GameObject("PausePopUp.png");
	popupUI->SetPosition(350, 450);

	restartB = new GameObject("RestartBtn.png");
	restartB->SetPosition(290, 400);

	homeB = new GameObject("HomeBtn.png");
	homeB->SetPosition(405, 400);

	popupUI->SetZOrder(-0.9);
	restartB->SetZOrder(-0.9);
	homeB->SetZOrder(-0.9);

	FreezeUI = new GameObject("IceDungeonBG.png");
	FreezeUI->SetPosition(350, 450);
	FreezeUI->SetZOrder(-0.9);

	Freeze = new GameObject("IceFrame.png");
	Freeze->SetPosition(350, 450);
	Freeze->SetZOrder(-0.9);

	//count = (13 % 2 != 0) ? 7 : 8;

	//gamelevel
	IsPaused = false;
	IsGameOver = IsWin = false;
	dropCount = blueCount = greenCount = redCount = 0;
	enemyCount = 0;
	timer = freezetime = Bosstimer = 0;
	
	curenemy = new Enemy((EnemyType)enemyCount);
	
	AudioManager::GetInstance()->PlayBGM(DEMO_SlimeBgm_INDEX);
	AudioManager::GetInstance()->setVolume(0.2);
	AudioManager::GetInstance()->LoadAudio("Resources/Ice.mp3", false, DEMO_Ice_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/Fire.mp3", false, DEMO_Fire_INDEX);
	AudioManager::GetInstance()->LoadAudio("Resources/Change.mp3", false, DEMO_Change_INDEX);

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 8; j++) {
			grids[i][j] = nullptr;
		}
	}
	for (int r = 0; r < 4; r++) {
		int count = ((r + dropCount) % 2 != 0) ? 7 : 8;
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
	float rp = (redCount / 15.0f);
	float bp = (blueCount / 15.0f);
	float gp = (greenCount / 15.0f);
	if (rp > 1)rp = 1;
	if (bp > 1)bp = 1;
	if (gp > 1)gp = 1;

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(525, 238 , 0.4);
	glVertex3f(525, 178 + (60.0f * rp), 0.4);
	glVertex3f(600, 178 + (60.0f * rp), 0.4);
	glVertex3f(600, 238 , 0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(480, 155, 0.4);
	glVertex3f(480, 95 + (60.0f * bp), 0.4);
	glVertex3f(550, 95 + (60.0f * bp), 0.4);
	glVertex3f(550, 155, 0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(575, 155 , 0.4);
	glVertex3f(575, 95+ (60.0f * gp), 0.4);
	glVertex3f(650, 95+ (60.0f * gp), 0.4);
	glVertex3f(650, 155 , 0.4);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void GameScene::Update(float dt)
{
	__super::Update(dt);
	
	if (IsGameOver) {
		SceneManager::GetInstance()->LoadScene("EndScene");
	}
	if (IsPaused) { return; }

	if (freezetime >= 0) {
		freezetime -= dt;
	}
	else {
		timer += dt;
		Bosstimer += dt;
		if (timer >= curenemy->CD) {
			curenemy->ChangeState(Att);
			AudioManager::GetInstance()->PlaySFX(11 + enemyCount);
			timer = 0;
			AddBubble();
			if (enemyCount == 2 && Bosstimer >= 25) {
				for (int r = 0; r < 13; r++) {
					for (int c = 0; c < 8; c++) {
						if (grids[r][c] != nullptr) {
							AudioManager::GetInstance()->PlaySFX(DEMO_Blind_INDEX);
							grids[r][c]->ChangeBlinded(true);
						}
					}
				}
				Bosstimer = 0;
			}
		}
		else if (timer >= 1) {
			curenemy->ChangeState(Wait);
		}
		
	}
	if (freezetime <= 0) {
		FreezeUI->SetZOrder(-0.9);
		Freeze->SetZOrder(-0.9);
	}
	
	

	if (curbubble->Ismoving) {
		if (IsConect(curbubble)) {
			cout << "IsConect" << endl;
			curbubble->Ismoving = false;

			int x, y;
			PosToGrid(curbubble->px, curbubble->py, y, x);
			
			grids[y][x] = curbubble;

			//
			if (y == 12) {
				cout << "GameOver" << endl;
				IsGameOver = true;
			}

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

	if (curenemy->IsDead) {
		delete(curenemy);
		curenemy = nullptr;
		enemyCount++;
		if (enemyCount < 3) {
			curenemy = new Enemy((EnemyType)enemyCount);
			AudioManager::GetInstance()->PlayBGM(1+ enemyCount);
			AudioManager::GetInstance()->setVolume(0.2);
			LevelUI->sprites->clear();
			LevelUI->AddFrame(Lvimg[enemyCount].c_str());
			timer = 0;
		}
	}
	if (enemyCount > 2) {
		enemyCount = 0;
		IsWin = true;
		IsGameOver = true;
	}
}

void GameScene::KeyDown(string keyCode)
{
	__super::KeyDown(keyCode);

	if (keyCode == "p" && IsPaused) {
		IsPaused = false;
		popupUI->SetZOrder(0.6);
		restartB->SetZOrder(0.8);
		homeB->SetZOrder(0.8);
	}
	if (keyCode == " " && !IsPaused) {
		IsPaused = true;
		popupUI->SetZOrder(-0.9);
		restartB->SetZOrder(-0.9);
		homeB->SetZOrder(-0.9);
	}

	if (keyCode == "w" && redCount>=15 ) {
		cout << "Red" << endl;
		AudioManager::GetInstance()->PlaySFX(DEMO_Fire_INDEX);
		curenemy->Hp -= 100;
		redCount = 0;
	}
	if (keyCode == "a" && blueCount >= 15) {
		cout << "blue" << endl;
		AudioManager::GetInstance()->PlaySFX(DEMO_Ice_INDEX);
		freezetime = 5;
		FreezeUI->SetZOrder(0.1);
		Freeze->SetZOrder(0.4);
		blueCount = 0;
	}
	if (keyCode == "d" && greenCount >= 15) {
		cout << "greed" << endl;
		AudioManager::GetInstance()->PlaySFX(DEMO_Change_INDEX);
		for (int r = 0; r < 13; r++) {
			for (int c = 0; c < 8; c++) {
				if (grids[r][c] != nullptr){
					grids[r][c]->ChangeColor();
				}
			}
		}
		greenCount = 0;
	}

	if (keyCode == "0") {
		curenemy->Hp -= 500;
	}
}

void GameScene::MouseOnClick(int button, int state, int x, int y)
{
	__super::MouseOnClick(button, state, x, y);
	if (stopBtn->CheckClicked(x, y)) {
		AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);
		cout << "clicked" << endl;
		IsPaused = true;

		popupUI->SetZOrder(0.6);
		restartB->SetZOrder(0.8);
		homeB->SetZOrder(0.8);
	}

	if (restartB->CheckClicked(x, y)) {
		AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);
		IsPaused = false;
		SceneManager::GetInstance()->LoadScene("GameScene");
		return;
	}
	if (homeB->CheckClicked(x, y)) {
		AudioManager::GetInstance()->PlaySFX(DEMO_SFX_INDEX);
		IsPaused = false;
		SceneManager::GetInstance()->LoadScene("TitleScene");
	}

	//
	if (IsGameOver || IsPaused) { return; }
	if (!curbubble->Ismoving) {
		AudioManager::GetInstance()->PlaySFX(DEMO_BubbleShoot_INDEX);
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
	if (angle > 40) angle = 40;
	if (angle < -40) angle = -40;
	
	pointLine->SetRotation(angle*-1);
	magicsk->SetRotation(angle * -1);
}

void GameScene::GridToPos(int y, int x, float& outX, float& outY)
{
	outX = 25 * (((y+ dropCount) % 2) + 1) + x * 25 * 2 + 25;
	outY = (900 - 40) - (25 + y * (25 * sqrt(3) + 3));
}

void GameScene::PosToGrid(float x, float y, int& outY, int& outX)
{
	outY = round((900 - 40 - y - 25) / (25 * sqrt(3) + 3));
	outX = round((x - (25 * (((outY + dropCount) % 2) + 1) + 25)) / (25 * 2));
}

void GameScene::AddBubble()
{
	if (grids[12][0] != nullptr) {
		IsGameOver = true;
		return;
	}

	for (int i = 11; i >= 0; i--) {
		for (int j = 0; j < 8;j++) {
			grids[i + 1][j] = grids[i][j];
			grids[i][j] = nullptr;
		}
	}

	dropCount++;
	int count = (dropCount % 2 != 0) ? 7 : 8;
	for (int c = 0; c < count; c++) {
		Bubble* bubble = new Bubble();
		float px, py;
		GridToPos(0, c, px, py);
		bubble->SetPosition(px, py);
		grids[0][c] = bubble;

	}

	for (int r = 0; r < 13; r++) {
		for (int c = 0; c < 8; c++) {
			if (grids[r][c] != nullptr) {
				float px, py;
				GridToPos(r, c, px, py);
				grids[r][c]->SetPosition(px, py);
			}
		}
	}

}


bool GameScene::IsConect(Bubble* bu)
{
	if (bu->py >= 835) {
		return true;
	}
	for (int i = 0; i < 13; i++) {
		int count = ((i + dropCount) % 2 != 0) ? 7 : 8;
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

		int damage = round(5 * pow(1.4, matchedBu->size()));
		BubbleType type = matchedBu->at(0)->colortype;
		if (curenemy != nullptr) {
			AudioManager::GetInstance()->PlaySFX(DEMO_BubbleDistory_INDEX);
			curenemy->TakeDamage(damage,(int)type);
		}
		switch (type) {
		case 0:
			greenCount += matchedBu->size();
			break;
		case 1:
			blueCount += matchedBu->size();
			break;
		case 2:
			redCount += matchedBu->size();
			break;
		}


		for (int i = 0; i < matchedBu->size(); i++) {
			new Effect(matchedBu->at(i)->px, matchedBu->at(i)->py);
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

void GameScene::CheckSameType(int y, int x, BubbleType buType, bool checked[13][8])
{
	if (y < 0 || y >= 13 || x < 0 || x >= 8) return;
	if (grids[y][x] == nullptr) return;
	if (checked[y][x]) return;
	if (grids[y][x]->colortype != buType) return;

	checked[y][x] = true;
	matchedBu->push_back(grids[y][x]);

	int count = ((y + dropCount) % 2 != 0) ? x : x - 1;

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
	int count = ((y + dropCount) % 2 != 0) ? x : x - 1;

	CheckEmpty(y - 1, count, checked);
	CheckEmpty(y - 1, count + 1, checked);
	CheckEmpty(y, x - 1, checked);
	CheckEmpty(y, x + 1, checked);
	CheckEmpty(y + 1, count, checked);
	CheckEmpty(y + 1, count + 1, checked);
}

