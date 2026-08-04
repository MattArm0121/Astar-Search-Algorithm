#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>

class Hypotrochoid {

public:
	static const int screenWidth = 1280;
	static const int screenHeight = 720;

	// To get the hypotrochoid
	struct Drawing {
		float innerRadius;
		float outerRadius;
		float distance;
		float revolutions = 2.0f;
		int pointsTotal = 2000;
		Color color;

		int frameCount = 0;

		bool ShowDrawingHead = true;

		int colorChanger = 7;

		float thick = 1;

		Drawing(float inner, float outer, float dist, Color COLOR) {
			innerRadius = inner;
			outerRadius = outer;
			distance = dist;
			color = COLOR;
		}

		void Draw() {
			// Need this so the angle is right on each draw call, PI used to make sure it's 360 degrees
			float dt = (2.0f * PI * revolutions) / pointsTotal;

			Vector2 prevPoint;

			for (int i = 0; i <= frameCount; i++) {
				float angle = i * dt;

				float x = (outerRadius - innerRadius) * cosf(angle) + distance * cosf((outerRadius - innerRadius) * angle / innerRadius);
				float y = (outerRadius - innerRadius) * sinf(angle) - distance * sinf((outerRadius - innerRadius) * angle / innerRadius);

				// For now putting it to the center of the screen
				Vector2 curPoint = { GetMouseX() + x, GetMouseY() + y};

				// Gotta do this so it doesn't draw on the first instance
				if (i > 0) {
					DrawLineEx(prevPoint, curPoint, thick, color);
				}
				prevPoint = curPoint;
			}

			if (ShowDrawingHead) 
			{
				DrawCircleLines(GetMouseX(), GetMouseY(), innerRadius, MAGENTA);
				DrawCircleLines(GetMouseX(), GetMouseY(), outerRadius, GRAY);
				DrawCircle(GetMouseX(), GetMouseY(), 5, MAGENTA);
			}
		}

		void Update() {
			// For showing the drawing frame by frame
			frameCount += 5;

			// For circle radius
			if (IsKeyDown(KEY_H))
				innerRadius += 5;
			else if (IsKeyDown(KEY_J))
				innerRadius -= 5;
			else if (IsKeyDown(KEY_K))
				outerRadius += 5;
			else if (IsKeyDown(KEY_L))
				outerRadius -= 5;

			// For showing drawing head
			if (IsKeyPressed(KEY_E))
				ShowDrawingHead = !ShowDrawingHead;

			// For changing pen color
			if (IsKeyPressed(KEY_R)) {
				colorChanger++;
			}

			if (colorChanger % 7 == 0)
				color = BLACK;
			else if (colorChanger % 7 == 1)
				color = RED;
			else if (colorChanger % 7 == 2)
				color = BLUE;
			else if (colorChanger % 7 == 3)
				color = YELLOW;
			else if (colorChanger % 7 == 4)
				color = GREEN;
			else if (colorChanger % 7 == 5)
				color = PURPLE;
			else
				color = ORANGE;

			// Line Thickness
			if (IsKeyDown(KEY_Z))
				thick += 0.1f;
			else if (IsKeyDown(KEY_X))
				thick -= 0.1f;

			// Distance
			if (IsKeyDown(KEY_C))
				distance += 1.0f;
			else if (IsKeyDown(KEY_V))
				distance -= 1.0f;
		}
	};

	Drawing drawingTool = { 0.0, 0.0, 0.0, RED };

	void Main();
	void Start();
	void Update();
};