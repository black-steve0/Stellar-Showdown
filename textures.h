#include "data.h"

void loadTetures() {
	bullet = ray::LoadTexture("assests/256px/Minigun_Medium_png_processed.png");
	asteroid = ray::LoadTexture("assests/256px/Asteroid 01_png_processed.png");
	spaceship1 = ray::LoadTexture("assests/256px/PlayerRed_Frame_01_png_processed.png");
	background = ray::LoadTexture("assests/PixelBackgroundSeamlessVertically.png");
	menuUI = ray::LoadTexture("assests/menu2.png");
	background.width = window_size.x;
	background.height = window_size.y;
	menuUI.width = window_size.x;
	menuUI.height = window_size.y;
	bullet.height = 30;
	bullet.width = 20;
}
