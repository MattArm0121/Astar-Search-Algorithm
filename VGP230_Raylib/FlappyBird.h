#pragma once
#include "raylib.h"
#include <vector>

class FlappyBird {
public:
	static const int screenWidth = 800;
	static const int screenHeight = 450;

	struct Player {
		Vector2 position;
		float radius = 20;
		Color color = BLACK;

		void Draw() {
			DrawCircleV(position, radius, color);
		}

		void Update() {
			if (IsKeyDown(KEY_SPACE)) 
				position.y -= 5;
			else 
				position.y += 1;
		}
	};

	struct Column {
		Rectangle topRect, bottomRect;

		bool gained = false; // Means this column has been scored

		Column(float x) {
			float width = 80;
			float topHeight = GetRandomValue(20, 300);
			float gap = GetRandomValue(80, 100);
			float y1 = 0;
			float y2 = topHeight + gap;
			float bottomHeight = screenHeight - y2;

			topRect = Rectangle{x, y1, width, topHeight};
			bottomRect = Rectangle{ x, y2, width, bottomHeight };
		}

		void Draw() {
			DrawRectangleRec(topRect, GRAY);
			DrawRectangleRec(bottomRect, GRAY);
		}

		void Update() {
			topRect.x -= 1;
			bottomRect.x -= 1;
		}

		bool CheckCollisionWithPlayer(Player player) {
			return CheckCollisionCircleRec(player.position, player.radius, topRect) ||
				CheckCollisionCircleRec(player.position, player.radius, bottomRect);
		}

		bool PlayerCrossed(Player player) {
			if (topRect.x < player.position.x + player.radius) {
				return true;
			}
		}
	};

	Player player = { 0 };
	int score = 0;

	std::vector<Column> columns;

	bool GameOver = false;

	void Main();
	void Start();
	void Update();
};