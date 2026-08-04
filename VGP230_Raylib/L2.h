#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "raymath.h"

#define CYAN CLITERAL(Color){ 0, 255, 255, 255 }

void mouseDrag() {
	InitWindow(800, 800, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	int y = 0;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		DrawCircle(GetMouseX(), GetMouseY(), 100, GREEN);

		EndDrawing();
	}

	CloseWindow();
}

void ColorOverlap() {
	InitWindow(800, 800, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	BlendMode myBlend = BLEND_MULTIPLIED;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		BeginBlendMode(myBlend);

		DrawCircle(400, GetMouseY(), 200, CYAN);
		DrawCircle(GetMouseX(), 800 - GetMouseY(), 200, YELLOW);
		DrawCircle(800 - GetMouseX(), 800 - GetMouseY(), 200, MAGENTA);

		EndBlendMode();

		EndDrawing();
	}

	CloseWindow();
}

void BouncingBall() {
	float gravity = 2.0f;
	float y = 50.0f;
	float speed = 1;

	InitWindow(360, 720, "Bouncing Ball"); // How big is your canvas?
	SetTargetFPS(60);

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		DrawCircle(180, y, 16, WHITE);

		float deltaTime = GetTime();

		if (speed >0) {
			y += gravity * deltaTime * deltaTime / 2;
		}
		else {
			y -= speed * deltaTime * deltaTime / 2;
			speed += gravity;
		}


		if (y + 16 > 720) {
			y = 720 - 16;
			speed = gravity * deltaTime;
			gravity *= -1;
		}
		else if (speed < 0) {
			gravity *= -1;
		}

		EndDrawing();
	}

	CloseWindow();
}

void DrawTriangleFunc() {
	InitWindow(360, 720, "DrawTriangle");
	SetTargetFPS(60);

	Vector2 top = Vector2{ 180, 50 };
	Vector2 left = Vector2{ 50, 720 - 50 };
	Vector2 right = Vector2{ 360 - 50, 720 - 50 };
	int radius = 20;

	bool attachTop = false;
	bool attachLeft = false;
	bool attachRight = false;

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();
			float topDist = Vector2Distance(mouse, top);
			float leftDist = Vector2Distance(mouse, left);
			float rightDist = Vector2Distance(mouse, right);

			if (topDist < radius) attachTop = true;
			else if (leftDist < radius) attachLeft = true;
			else if (rightDist < radius) attachRight = true;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			attachTop = attachLeft = attachRight = true;
		}
		if (attachTop) top = GetMousePosition();
		if (attachLeft) left = GetMousePosition();
		if (attachRight) right = GetMousePosition();

		DrawTriangle(top, left, right, GREEN);
		DrawCircleV(top, 20, WHITE);
		DrawCircleV(left, 20, WHITE);
		DrawCircleV(right, 20, WHITE);

		EndDrawing();
	}

	CloseWindow();
}

void DrawPolygonFunc() {
	InitWindow(800, 800, "Game"); // How big is your canvas?
	SetTargetFPS(60);

	Vector2 centre = Vector2{ 400, 400 };
	int r = 250;
	int sides = 6;

	std::vector<Vector2> corners;

	for (int i = 0; i < sides; i++) {
		float angle = 360 / sides * i;
		float x = centre.x + cos(angle * DEG2RAD) * r;
		float y = centre.y + sin(angle * DEG2RAD) * r;


		Vector2 vertex = Vector2{ x, y };
		corners.push_back(vertex);
	}

	// Game Loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		for (int i = 0; i < corners.size() - 1; i++) {
			DrawTriangle(centre, corners[i + 1], corners[i], WHITE);
		}

		DrawTriangle(centre, corners[0], corners[corners.size() - 1], WHITE);

		for (Vector2 any : corners) {
			DrawCircleV(any, 10, BLACK);
		}

		EndDrawing();
	}

	CloseWindow();
}



// ASSIGNMENT 2

bool shapeCollision(int s1X, int s1Y, int s2X, int s2Y, int r) {
	int X = s1X - s2X;
	int Y = s1Y - s2Y;

	int distanceSQRT = (X * X) + (Y * Y);
	int radiusSum = 2 * r;

	return distanceSQRT <= radiusSum * radiusSum;
}

void matchGame() {
	InitWindow(1920, 1080, "Match Game"); 
	SetTargetFPS(60);

	Vector2 CircleCen = Vector2{900, 540};
	Vector2 HexCen = Vector2{ 800, 600 };
	Vector2 PentCen = Vector2{1000, 500};
	Vector2 TriangleCen = Vector2{ 600, 540 };

	bool attachCircle = false;
	bool attachHex = false;
	bool attachPent = false;
	bool attachTriangle = false;

	int radius = 50;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		// Mouse for all of them
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();

			// Circle
			float circleDist = Vector2Distance(mouse, CircleCen);
			// Hexagon
			float hexDist = Vector2Distance(mouse, HexCen);
			// Pentagon
			float pentDist = Vector2Distance(mouse, PentCen);
			// Triangle
			float triangleDist = Vector2Distance(mouse, TriangleCen);

			if (circleDist < radius) attachCircle = true;
			else if (hexDist < radius) attachHex = true;
			else if (pentDist < radius) attachPent = true;
			else if (triangleDist < radius) attachTriangle = true;
		}

		if (attachCircle) CircleCen = GetMousePosition();
		else if (attachHex) HexCen = GetMousePosition();
		else if (attachPent) PentCen = GetMousePosition();
		else if (attachTriangle) TriangleCen = GetMousePosition();

		if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
			attachCircle = attachHex = attachPent = attachTriangle = false;
		}

		// Drawing the goals as they won't move
		DrawCircle(50, 50, radius, BLACK);
		DrawPoly({ 50, 1000 }, 6, radius, 90, BLACK);
		DrawPoly({ 1850, 1000 }, 3, radius, 90, BLACK);
		DrawPoly({1800, 50}, 5, radius, 90, BLACK);

		// Objects to get into the spot
		if (!shapeCollision(CircleCen.x, CircleCen.y, 50, 50, radius)) {
			DrawCircleV(CircleCen, radius, RED);
		}
		if (!shapeCollision(HexCen.x, HexCen.y, 50, 1000, radius)) {
			DrawPoly({ HexCen }, 6, radius, 90, BLUE);
		}
		if (!shapeCollision(PentCen.x, PentCen.y, 1800, 50, radius)) {
			DrawPoly({ PentCen }, 5, radius, 90, YELLOW);
		}
		if (!shapeCollision(TriangleCen.x, TriangleCen.y, 1850, 1000, radius)) {
			DrawPoly({ TriangleCen }, 3, radius, 90, GREEN);
		}
		EndDrawing();
	}

	CloseWindow();
}