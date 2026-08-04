#pragma once
#include "raylib.h"
#include "raymath.h"
#include <algorithm>

struct Particle {
	Vector2 center = { 0, 0 };
	float radius = 0;
	Color color = BLACK;
	float speed = 0;
	// float angle = 0;
	// float gravity = 10;
	bool active = false;
	int coloralphaCheck = 0;
	int tempalpha = 0;

	/*
	Color RandomColor(void) {
		return CLITERAL(Color) {
			static_cast<unsigned char>(GetRandomValue(0, 255)),
			static_cast<unsigned char>(GetRandomValue(0, 255)),
			static_cast<unsigned char>(GetRandomValue(0, 255)),
			255
		};
	}
	*/

	void activate(Vector2 cen) {
		this->center = cen;
		this->radius = GetRandomValue(4, 8);
		// this->angle = GetRandomValue(0, 360);
		this->speed = GetRandomValue(4, 8);
		this->color = RED;
		color.a = 255;

		active = true;
	}

	void Update() {
		/*
		center.x += cos(angle * DEG2RAD) * std::max(speed, 1.0f);
		center.y += sin(angle * DEG2RAD) * std::max(speed, 1.0f) + gravity;

		if (color.a > 0)
			color.a -= 3;
		else
			active = false;

		radius += 0.1f;
		speed -= 0.5f;
		*/

		// Changing color

		tempalpha = color.a;

		if (color.a > 175) {
			this->color = RED;
		}
		else if (color.a > 90) {
			this->color = ORANGE;
		}
		else {
			this->color = YELLOW;
		}

		color.a = tempalpha;

		// Fading out
		if (color.a > 0) {
			coloralphaCheck = color.a;
			if (coloralphaCheck - 3 > 0)
				color.a -= 3;
			else
				color.a = 0;
		} 
		else
			active = false;

		center.x += GetRandomValue(-10, 10);
		center.y -= speed;
		radius = std::max(radius - 0.05f, 0.0f);
	}

	void Draw() {
		if(!this->active)
			return;

		this->Update();

		DrawCircleV(center, radius, color);
	}
};