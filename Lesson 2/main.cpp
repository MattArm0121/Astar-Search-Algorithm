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