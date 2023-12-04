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


Asteroid::Asteroid(ray::Vector2 p_position, ray::Vector2 p_size, int p_type, int p_speed, int p_health = 10, bool p_reflective = 0) {
	position = p_position;
	size = p_size;
	type = p_type;
	health = p_health;
	reflective = p_reflective;
	speed = p_speed;

	vector += ray::Vector2(((double)(rand() % 10) - (rand() % 10))/10, 1);
}

void Asteroid::update(int id) {
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		int x = window_size.x;
		position = ray::Vector2(rand() % x, -size.y);
	}
	if (ray::CheckCollisionRecs(ray::Rectangle(), ray::Rectangle())) {
		int x = window_size.x;
		position = ray::Vector2(rand() % x, -size.y);
	}
	position += vector * speed;
}

void Asteroid::exitScreen() {

}

void Asteroid::hit() {

}

void Asteroid::explode() {

}

void Asteroid::reflect() {

}

void Asteroid::draw() {
	ray::DrawRectangle(position.x, position.y, size.x, size.y, WHITE);
}

void Bullet::update() {

}

void Bullet::collide() {
	int x = window_size.x;

}

void update(double deltatime) {

}

void gameplay(double deltatime) {
}
