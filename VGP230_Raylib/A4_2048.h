#pragma once
#include "raylib.h"
#include <vector>
#include <string>

class A4_2048 {
public:
	static const int screenWidth = 800;
	static const int screenHeight = 800;

	struct GridTile {
		Rectangle tile;
		int row = 0;
		int column = 0;

		GridTile(float x, float y) {
			row = x;
			column = y;
			tile = Rectangle{x*200, y*200, 200, 200};
		}

		void Draw() {
			DrawRectangleLinesEx(tile, 5, BLACK);
		}

		bool Occupied(int x, int y) {
			return x == row && y == column;
		}
	};

	std::vector<GridTile> grid;

	struct PlayingTile {
		int rowLocation, columnLocation, num;

		PlayingTile(int row, int column) {
			rowLocation = row;
			columnLocation = column;
			num = 2;
		}

		void Draw() {
			DrawRectangle(200*rowLocation+10, 200*rowLocation+10, 180, 180, ORANGE);
			DrawText(std::to_string(num).c_str(), 200 * rowLocation + 90, 200 * rowLocation + 90, 40, BLACK);
		}

		bool Occupied(int row, int column) {
			return rowLocation == row && columnLocation == column;
		}
	};

	std::vector<PlayingTile> tiles;

	void Main();
	void Start();
	void Update();
};

/*
* Steps: 
* Spawn in two 2s on a random tile on the grid
* Whenever movement is done, first move all tiles in that direction
* If a collision is detected, add the two together
* Spawn a new tile on every move within an empty location on the grid
*/