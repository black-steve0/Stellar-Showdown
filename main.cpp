#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"
#include "menu.h"
#include "textures.h"

void main() {
	window.Init();

	run = 1;
	gameRunning = 0;

	font = ray::LoadFont("resources/fonts/romulus.png");

	loadTetures();

	start = std::chrono::high_resolution_clock::now();
	pstart = std::chrono::high_resolution_clock::now();

	while (run) {
		window.ProcessPerFrame();
	}

	ray::UnloadTexture(spaceship1);

	ray::CloseWindow();
}