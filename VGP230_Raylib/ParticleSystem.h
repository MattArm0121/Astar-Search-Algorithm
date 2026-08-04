#pragma once
#include "raylib.h"
#include <vector>
#include "Particle.h"

class ParticleSystem
{
public:
#define POOL_SIZE 1000
	std::vector<Particle> pool;

	void Main(); // Raylib stuff
	void Start(); // Unity-style start of project
	void Update(); // Unity-style update per frame
};

