#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"
#include "menu.h"
#include "textures.h"

void main() {
	window.Init();

	for (int i = 0; i < controls.size(); i++) {
		char text[2] = { defaultControls[i], '\0'};
		controlButtons.push_back(ControlButton(Vector2f(25 + 250 + 10, 125 + 90 * i), Vector2f(250, 75), text));
	}

	run = 1;
	gameRunning = 0;

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