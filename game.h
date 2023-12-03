#pragma once

#include "data.h"

Player::Player(ray::Vector2 p_size) {
	size = p_size;
	position = ray::Vector2(window_size.x / 2 - size.x / 2, window_size.y - size.y - 10);
}

void Player::draw() {
	ray::DrawRectangle(position.x, position.y, size.x, size.y, WHITE);
}

void Player::move(ray::Vector2 vector) {
	if (position.x + (vector.x * speed) > 0 and position.x + (vector.x * speed) < window_size.x - size.x and position.y + (vector.y * speed) > 0 and position.y + (vector.y * speed) < window_size.y - size.y) {
		position += vector * speed;
	}

}


void Asteroid::update(double deltatime) {

}

void Asteroid::exitScreen() {

}

void Asteroid::hit() {

}

void Asteroid::explode() {

}

void Asteroid::reflect() {

}
