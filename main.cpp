#include <iostream>
#include <raylib.h>
#include <stvlib.h>
#include "game.h"

Game game(ray::Vector2(700,900), "Stellar Showdown", 60);

int main()
{
	game.Init();

	int run = 1;

	while (run) {
		if (ray::WindowShouldClose()) run = 0;

		ray::BeginDrawing();
		ray::EndDrawing();
		ray::ClearBackground(SKYBLUE);
	}

	ray::CloseWindow();
}

