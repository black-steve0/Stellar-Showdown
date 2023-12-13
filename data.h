#pragma once

#include "classes.h"

#define window_size ray::Vector2(900, 1000)

int stage;
int difficulty;
int x = window_size.x;
int run;

std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> pstart;
std::chrono::time_point<std::chrono::steady_clock> tick;

ray::Texture spaceship1;
ray::Texture spaceship2;
ray::Texture asteroid;
ray::Font font;
ray::Texture background;
ray::Texture menuUI;
ray::Texture shieldTexture;
std::vector<ray::Texture> powerUPTextures;
std::vector<ray::Texture> bulletTextures;

Player player(ray::Vector2(125, 125));
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
