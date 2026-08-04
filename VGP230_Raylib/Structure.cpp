#include "Structure.h"

// Render loop of the game
void Structure::Main() {
	Start();

	InitWindow(600, 600, "Unity-Style Raylib Structure");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void Structure::Start() {

}

void Structure::Update() {

}