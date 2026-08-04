#include "FlappyBird.h"
#include <string>

// Render loop of the game
void FlappyBird::Main() {
	Start();

	InitWindow(screenWidth, screenHeight, "Unity-Style Raylib Structure");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		//ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void FlappyBird::Start() {
	player.position = Vector2{80, (float)screenHeight/2 - player.radius};

	for (int i = 0; i < 5; i++) {
		Column col = Column(200 + 250 * i);
		columns.push_back(col);
	}
}

void FlappyBird::Update() {
	for (int i = 0; i < columns.size(); i++) {
		if (GameOver) break;

		columns[i].Update();
		columns[i].Draw();

		GameOver = columns[i].CheckCollisionWithPlayer(player);

		if (columns[i].PlayerCrossed(player) && !columns[i].gained) {
			columns[i].gained = true;
			score++;
		}
	}

	DrawText(std::to_string(score).c_str(), 20, 20, 20, BLACK);

	auto smlst = std::find_if(columns.begin(), columns.end(), [](Column col){
		return col.topRect.x + col.topRect.width < 0;
		});

	if (smlst != columns.end()) {
		auto lgst = std::max_element(columns.begin(), columns.end(), [](Column a, Column b) {
			return a.topRect.x < b.topRect.x;
			});

		smlst->topRect.x = lgst->topRect.x + 250;
		smlst->bottomRect.x = lgst->bottomRect.x + 250;
		smlst->gained = false;
	}

	player.Update();
	player.Draw();

	/*
	if (columns[0].topRect.x < 0 - columns[0].topRect.width) {

		Column front = columns[0];
		columns.erase(columns.begin());

		front.topRect.x = columns.back().topRect.x + 250;
		front.bottomRect.x = columns.back().bottomRect.x + 250;

		columns.push_back(front);
		*/

		/*
		* Secondary way code I never finished
		*
		int smallestXLocation = 0;
		int biggesttXLocation = 0;

		for (int i = 0; i < columns.size() - 1; i++) {
			// Checking smallest
			if (columns[i].topRect.x <= columns[smallestXLocation].topRect.x)

		}

	}
	*/
}