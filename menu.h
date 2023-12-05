#pragma once

#include "game.h"

void menu() {
	ray::Vector2 size(500,150);
	ray::DrawRectangle(window_size.x/2 - size.x/2, window_size.y/2 - size.y/2, size.x, size.y, WHITE);
	ray::DrawText("PLAY", window_size.x / 2 - (65 * 3)/2, window_size.y / 2 - 64, 64, GRAY);
}