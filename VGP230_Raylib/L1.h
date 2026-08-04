#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

std::string enterText() {
	std::string text;
	std::cout << "Enter text: ";
	std::cin >> text;
	return text;
}

void drawTemplate() {
	InitWindow(500, 500, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		EndDrawing();
	}

	CloseWindow();
}

void BasicDrawing() {
	InitWindow(500, 500, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	int r = 500 / 8;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		DrawCircle(r, r, r, RED);
		DrawCircle(r * 3, r, r, BLUE);
		DrawCircle(r * 5, r, r, YELLOW);
		DrawCircle(r * 7, r, r, WHITE);

		int posX = 20;
		int posY = 500 / 2 - 100 / 2;
		int w = 500 - 20 - 20;
		int h = 100;

		DrawRectangle(posX, posY, w, h, PINK);

		DrawPoly(Vector2{ 250, 250 }, 5, 150, 90, BLACK);

		EndDrawing();
	}

	CloseWindow();
}

void drawText(std::string text) {
	InitWindow(500, 500, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		int fontSize = 40;

		int textWidth = MeasureText(text.c_str(), fontSize);
		int buttonWidth = textWidth + 20 + 20;
		int buttonHeight = fontSize + 10 + 10;

		int buttonX = 250 - buttonWidth / 2;
		int buttonY = 250 - buttonHeight / 2;

		int txtX = 250 - textWidth / 2;
		int txtY = 250 - fontSize / 2;

		Rectangle rect = Rectangle{ (float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight };
		DrawRectangleRounded(rect, .4, 0, ORANGE);
		DrawText(text.c_str(), txtX, txtY, fontSize, WHITE);

		EndDrawing();
	}

	CloseWindow();
}

void MoveCircle() {
	int w = 500; int h = 500; int r = 50;
	int cenX = w / 2; int curY = 0 + r;
	InitWindow(w, h, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	bool goingUp = false;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		if (goingUp) {
			curY--;
			if (curY == 0 + r) {
				goingUp = false;
			}
		}
		else {
			curY++;
			if (curY == h - r) {
				goingUp = true;
			}
		}

		DrawCircle(cenX, curY, r, RED);
		EndDrawing();
	}

	CloseWindow();
}

int wallCollision(int x, int y, int r, int w, int h, int cur_dir) {
	bool xHit = false;
	bool yHit = false;

	// X Check
	if (0 > x - r) {
		xHit = true;
	}
	else if (x + r > w) {
		xHit = true;
	}

	// Y Check
	if (0 > y - r) {
		yHit = true;
	}
	else if (y + r > h) {
		yHit = true;
	}

	// X-hit
	if (xHit) {
		// Gonna look ugly...
		if (cur_dir == 1) {
			cur_dir = 3;
		}
		else if (cur_dir == 2) {
			cur_dir = 4;
		}
		else if (cur_dir == 3) {
			cur_dir = 1;
		}
		else {
			cur_dir = 2;
		}
	}
	// Y-Hit
	else if (yHit) {
		// Gonna look ugly...
		if (cur_dir == 1) {
			cur_dir = 2;
		}
		else if (cur_dir == 2) {
			cur_dir = 1;
		}
		else if (cur_dir == 3) {
			cur_dir = 4;
		}
		else {
			cur_dir = 3;
		}
	}
	return cur_dir;
}

bool ballCollision(int redX, int redY, int blueX, int blueY, int r) {
	int X = redX - blueX;
	int Y = redY - blueY;

	int distanceSQRT = (X * X) + (Y * Y);
	int radiusSum = 2 * r;

	return distanceSQRT <= radiusSum * radiusSum;
}

void BounceBall() {
	int w = 500; int h = 500; int r = 50;
	int redCenX = 100; int redCenY = 150;
	int blueCenX = 400; int blueCenY = 350;
	int red_dir = (std::rand() % 4) + 1; // for 1-4
	int blue_dir = (std::rand() % 4) + 1; // for 1-4
	InitWindow(w, h, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		// Red Movement
		if (red_dir == 1) { // Left Up, x--, y--
			redCenX--; redCenY--;
		}
		else if (red_dir == 2) { // Left Down, x--, y++
			redCenX--; redCenY++;
		}
		else if (red_dir == 3) { // Right Up, x++, y--
			redCenX++; redCenY--;
		}
		else { // Right Down, x++, y++
			redCenX++; redCenY++;
		}

		// Blue Movement
		if (blue_dir == 1) { // Left Up, x--, y--
			blueCenX--; blueCenY--;
		}
		else if (blue_dir == 2) { // Left Down, x--, y++
			blueCenX--; blueCenY++;
		}
		else if (blue_dir == 3) { // Right Up, x++, y--
			blueCenX++; blueCenY--;
		}
		else { // Right Down, x++, y++
			blueCenX++; blueCenY++;
		}

		DrawCircle(redCenX, redCenY, r, RED);
		DrawCircle(blueCenX, blueCenY, r, BLUE);

		red_dir = wallCollision(redCenX, redCenY, r, w, h, red_dir);
		blue_dir = wallCollision(blueCenX, blueCenY, r, w, h, blue_dir);

		if (ballCollision(redCenX, redCenY, blueCenX, blueCenY, r)) {
			int temp = red_dir;
			red_dir = blue_dir;
			blue_dir = temp;
		}


		EndDrawing();
	}

	CloseWindow();
}