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

	//shield.active = 1;
	//shield.start = std::chrono::high_resolution_clock::now();

	font = LoadFont("resources/fonts/romulus.png");

	loadTextures();
	Image icon = LoadImage("assests/256px/PlayerRed_Frame_01_png_processed.png");
	SetWindowIcon(icon);

	ustart = std::chrono::high_resolution_clock::now();
	pstart = std::chrono::high_resolution_clock::now();
	rogueStart = std::chrono::high_resolution_clock::now();

	while (run) {
		window.ProcessPerFrame();
	}

	CloseWindow();
}