#include "ParticleSystem.h"

void ParticleSystem::Main() {
	Start();

	InitWindow(600, 600, "Unity-Style Raylib Particle System");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginBlendMode(BLEND_ALPHA);

		Update();

		EndBlendMode();

		EndDrawing();
	}
}

void ParticleSystem::Start() {
	for (int i = 0; i < POOL_SIZE; i++) {
		pool.push_back(Particle());
	}
}

void ParticleSystem::Update() {
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		int rate = GetRandomValue(2, 5);

		for (int i = 0; i < rate; i++) {
			for (int j = 0; j < POOL_SIZE; j++) {
				if (!pool[j].active) {
					pool[j].activate(GetMousePosition());
					break;
				}
			}
		}
	}

	for (int i = 0; i < POOL_SIZE; i++)
		pool[i].Draw();
}