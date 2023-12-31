#include "data.h"

void loadTextures() {

	powerUPTextures = {
		LoadTexture("assests/256px/Powerup_Ammo_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Energy_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Health_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Rockets_png_processed.png"),
		LoadTexture("assests/256px/Powerup_Shields_png_processed.png"),
		LoadTexture("assests/256px/gearPowerUp.png")
	};

	bulletTextures = {
		LoadTexture("assests/0.png"),
		LoadTexture("assests/256px/Laser_Medium_png_processed.png"),
		LoadTexture("assests/256px/Plasma_Medium_png_processed.png"),
	};

	spaceshipTexture = {
		LoadTexture("assests/256px/PlayerRed_Frame_01_png_processed.png"),
		LoadTexture("assests/256px/PlayerBlue_Frame_01_png_processed.png")
	};

	buttonTextures = {
		LoadTexture("assests/normalButton.png"),
		LoadTexture("assests/squareButtonDarkBlue.png"),
		LoadTexture("assests/squareButtonBlue.png"),
		LoadTexture("assests/squareButtonGold.png"),
		LoadTexture("assests/squareButtonMixedBlue.png"),
		LoadTexture("assests/normalButtonMixedBlue.png"),
	};

	for (Texture& texture : bulletTextures) {
		texture.width = 25;
		texture.height = 40;
	}

	spaceshipTexture[0].width = 125;
	spaceshipTexture[0].height = 125;
	spaceshipTexture[1].width = 125;
	spaceshipTexture[1].height = 125;

	for (int i = 0; i < 13; i++) {
		std::string name = "assests/256px/explosion" + std::to_string(i) + ".png";
		explosionTextures.push_back(LoadTexture(name.c_str()));
		explosionTextures[i].width = 150;
		explosionTextures[i].height = 150;
	}

	for (Texture& texture: powerUPTextures) {
		texture.width = 75;
		texture.height = 40;
	}

	for (int i = 0; i < 13; i++) {
		std::string name = "assests/healthbar/" + std::to_string(i) + ".png";
		healthTextures.push_back(LoadTexture(name.c_str()));
		healthTextures[i].width = 300;
		healthTextures[i].height = 65;
	}

	sideTurretTexture = LoadTexture("assests/256px/Enemy02_Teal_Frame_1_png_processed.png");
	fireSpeedIcon = LoadTexture("assests/256px/GunTurret_Orange_png_processed.png");
	shieldTexture = LoadTexture("assests/shield.png");
	rocketTexture = LoadTexture("assests/rocket.png");
	gearTexture = LoadTexture("assests/gear/0.png");
	rogueEnemyTexture = LoadTexture("assests/256px/Enemy02Green_Frame_1_png_processed.png");
	logo = LoadTexture("assests/logo.png");
	backButton = LoadTexture("assests/back.png");
	miniBulletTexture = LoadTexture("assests/256px/Proton_Medium_png_processed.png");
	asteroid = LoadTexture("assests/256px/Asteroid 01_png_processed.png");
	shieldTexture.width = 200;
	shieldTexture.height = 200;
	background = LoadTexture("assests/PixelBackgroundSeamlessVertically.png");
	menuUI = LoadTexture("assests/menu2.png");
	background.width = window_size.x;
	background.height = window_size.y;
	menuUI.width = window_size.x;
	menuUI.height = window_size.y;
	backButton.height = 75;
	backButton.width = 75;
	miniBulletTexture.height = 10;
	miniBulletTexture.width = 10;

	font = LoadFont("assests/AtariGames.ttf");
}
