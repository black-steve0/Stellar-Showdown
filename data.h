#pragma once

#include "classes.h"

#define window_size ray::Vector2(900, 1000)

int stage;
int difficulty;
int score = 0;
int highscore = 0;
int x = window_size.x;

Player player(ray::Vector2(125, 125));
Window window(window_size, "Stellar Showdown", 60);
std::vector<Bullet> bullets;
std::vector<Asteroid> asteroids;
std::vector<Button> buttons;

bool gameRunning;
