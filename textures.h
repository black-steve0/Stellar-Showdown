#include "data.h"

void loadTetures() {

	powerUPTextures = {
		LoadTexture("assests/256px/Powerup_Ammo_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Energy_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Health_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Rockets_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Shields_png_processed.png")
	};

	bulletTextures = {
		LoadTexture("assests/256px/Minigun_Medium_png_processed.png"),
		LoadTexture("assests/256px/Laser_Medium_png_processed.png"),
		LoadTexture("assests/256px/Plasma_Medium_png_processed.png"),
	};

	for (Texture& texture: powerUPTextures) {
		texture.width = 75;
		texture.height = 40;
	}

	backButton = LoadTexture("assests/back.png");
	shieldTexture = LoadTexture("assests/256px/Shield.png");
	asteroid = LoadTexture("assests/256px/Asteroid 01_png_processed.png");
	spaceship1 = LoadTexture("assests/256px/PlayerRed_Frame_01_png_processed.png");
	spaceship2 = LoadTexture("assests/256px/PlayerBlue_Frame_01_png_processed.png");
	background = LoadTexture("assests/PixelBackgroundSeamlessVertically.png");
	menuUI = LoadTexture("assests/menu2.png");
	background.width = window_size.x;
	background.height = window_size.y;
	menuUI.width = window_size.x;
	menuUI.height = window_size.y;
	backButton.height = 75;
	backButton.width = 75;
}
