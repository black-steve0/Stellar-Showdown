#pragma once

#include "classes.h"

#define window_size Vector2(900, 1000)

int stage;
int difficulty;
int x = window_size.x;
int run;

std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> pstart;
std::chrono::time_point<std::chrono::steady_clock> tick;

Texture spaceship1;
Texture spaceship2;
Texture asteroid;
Font font;
Texture background;
Texture menuUI;
Texture shieldTexture;
Texture backButton;
std::vector<Texture> powerUPTextures;
std::vector<Texture> bulletTextures;

Player player(Vector2(125, 125));
Window window(window_size, "Stellar Showdown", 60);

int BulletIdCount = 1;
int PowerUPIdCount = 1;

std::vector<Bullet> bullets = {};
std::vector<Asteroid> asteroids = {};
std::vector<Button> buttons;
std::vector<PowerUP> powerUPs;

int score = 0;
int bulletsize = 25;
int asteroidsize = 100;
float firespeed;
int bulletType = 1;
float damage;

bool gameRunning;
int shopPage = 1;
int page = 0;

int highscore = 0;
float totalcoins = 0;
