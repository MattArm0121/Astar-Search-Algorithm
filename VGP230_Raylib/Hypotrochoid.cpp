#include "Hypotrochoid.h"

void Hypotrochoid::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "Spirograph Drawer");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void Hypotrochoid::Start()
{
	drawingTool = Drawing(20, 50, 20, RED);
}

void Hypotrochoid::Update()
{
	DrawText("Increase Inner Radius: Press h", 20, 20, 20, BLACK);
	DrawText("Decrease Inner Radius: Press j", 20, 50, 20, BLACK);
	DrawText("Increase Outer Radius: Press k", 20, 80, 20, BLACK);
	DrawText("Decrease Outer Radius: Press l", 20, 110, 20, BLACK);
	DrawText("Toggle Drawing Head: Press e", 20, 140, 20, BLACK);
	DrawText("Change Pen Color: Press r", 20, 170, 20, BLACK);
	DrawText("Increase Line Thickness: Press z", 20, 200, 20, BLACK);
	DrawText("Decrease Line Thickness: Press x", 20, 230, 20, BLACK);
	DrawText("Increase Distance: Press c", 20, 260, 20, BLACK);
	DrawText("Decrease Distance: Press v", 20, 290, 20, BLACK);

	drawingTool.Draw();
	drawingTool.Update();
}
