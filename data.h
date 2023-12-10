#pragma once

#include "classes.h"

#define window_size ray::Vector2(900, 1000)

int stage;
int difficulty;
int score = 0;
int highscore = 0;
int x = window_size.x;

ray::Texture bullet;
ray::Texture spaceship1;
ray::Texture asteroid;
ray::Font font;
ray::Texture background;
ray::Texture menuUI;

Player player(ray::Vector2(125, 125));
Window window(window_size, "Stellar Showdown", 60);

std::vector<Bullet> bullets = {};
std::vector<int> deadBullets = {};
std::vector<Asteroid> asteroids = {};
std::vector<Button> buttons;

int btype;
int damage;

bool gameRunning;
