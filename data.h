#pragma once

#include "classes.h"

#define window_size ray::Vector2(900, 1000)

int stage;
int difficulty;
int x = window_size.x;
int page = 0;

ray::Texture bullet;
ray::Texture spaceship1;
ray::Texture asteroid;
ray::Font font;
ray::Texture background;
ray::Texture menuUI;
ray::Texture shieldTexture;
std::vector<ray::Texture> powerUPTextures;

Player player(ray::Vector2(125, 125));
Window window(window_size, "Stellar Showdown", 60);

int BulletIdCount = 1;
int PowerUPIdCount = 1;

std::vector<Bullet> bullets = {};
std::vector<Asteroid> asteroids = {};
std::vector<Button> buttons;
std::vector<PowerUP> powerUPs;

float firespeed;
int btype;
float damage;

bool gameRunning;

int score = 0;
int highscore = 0;
float totalcoins = 0;