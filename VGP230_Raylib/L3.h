#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "raymath.h"

void collisionTest() {
	InitWindow(500, 500, "Collision Test");
	SetTargetFPS(60);

	Rectangle boxA = { 50, 100, 300, 50 };
	Rectangle boxB = { 50, 300, 300, 50 };
	int gravity = 1;
	bool collision = false;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		boxA.y += gravity;
		collision = CheckCollisionRecs(boxA, boxB);

		if (collision) {
			DrawText("Collided", 100, 100, 30, BLUE);
		}

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			if (CheckCollisionPointRec(GetMousePosition(), boxB)) {
				DrawText("Mouse Collided", 100, 200, 30, BLUE);
			}
		}
		 

		DrawRectangleRec(boxA, RED);
		DrawRectangleRec(boxB, GREEN);

		EndDrawing();
	}

	CloseWindow();
}

void UIButtonFunc() {
	InitWindow(500, 500, "UI Button Test");
	SetTargetFPS(60);

	Rectangle buttonRect = {100, 100, 300, 54};
	Rectangle shadowRect = buttonRect;
	shadowRect.y += 4;
	Color passiveColor = YELLOW;
	Color curColor = passiveColor;
	Color hoverColor = BLUE;
	Color clickColor = GREEN;
	Color shadowColor = Color{30, 30, 30, 100};

	Vector2 mouse = { 0, 0 };

	while (!WindowShouldClose()) {
		mouse = GetMousePosition();

		curColor = passiveColor;

		if (CheckCollisionPointRec(mouse, buttonRect)) {
			curColor = hoverColor;

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				curColor = clickColor;
		}
		
		BeginDrawing();
		ClearBackground(GRAY);

		DrawRectangleRounded(shadowRect, 0.25, 8, shadowColor);
		DrawRectangleRounded(buttonRect, 0.25, 8, curColor);


		EndDrawing();
	}

	CloseWindow();
}

void LoadTextureFunc() {
	InitWindow(500, 500, "Load Texture Test");
	SetTargetFPS(60);

	std::cout << GetWorkingDirectory() << std::endl;

	Image myImg = LoadImage("resources/myimage.png");
	if (myImg.data != NULL) {
		std::cout << "Image loaded successfully";
	}
	else {
		std::cout << "Image loaded failed";
	}
	ImageResize(&myImg, 200, 200);

	Texture2D myTexture = LoadTextureFromImage(myImg);
	UnloadImage(myImg);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		DrawTexture(myTexture, 150, 150, WHITE);


		EndDrawing();
	}

	CloseWindow();
}