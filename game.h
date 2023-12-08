#pragma once

#include "data.h"

void endGame() {
	gameRunning = 0;
	asteroids.clear();
}

Player::Player(ray::Vector2 p_size) {
	size = p_size;
	position = ray::Vector2(window_size.x / 2 - size.x / 2, window_size.y - size.y - 10);
}

void Player::draw() {
	spaceship1.width = 125;
	spaceship1.height = 125;
	ray::DrawTexture(spaceship1, position.x, position.y, WHITE);
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

void Asteroid::update() {
	int x = window_size.x;
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		
		position = ray::Vector2(rand() % x, -size.y);
	}
	if (ray::CheckCollisionRecs(ray::Rectangle(position.x, position.y, size.x, size.y), ray::Rectangle(player.position.x, player.position.y, player.size.x, player.size.y))) {
		player.health -= (int)size.x / 75;

		if (type == 2) {
			ray::DrawCircle(position.x, position.y, size.x, RED);
			if (ray::CheckCollisionCircleRec(position, size.x, ray::Rectangle(player.position.x, player.position.y, player.size.x, player.size.y))) {
				player.health -= 3;
			}
		}

		position = ray::Vector2(rand() % x, rand() % 100 - size.y);
		type = rand() % 3;
		health = 10;

		if (player.health <= 0) {
			endGame();
		}
	}

	position += vector * speed;
}

void Asteroid::collided(int type) {
	position = ray::Vector2(rand() % x, -(rand() % 100) - size.y);
	type = rand() % 3;
	health = 10;
	score++;
}

void Asteroid::draw() {
	asteroid.width = 125;
	asteroid.height = 125;
	if (type == 2) {
		ray::DrawTexture(asteroid, position.x - size.x/2, position.y - size.y/2, RED);
	}
	else {
		ray::DrawTexture(asteroid, position.x, position.y, WHITE);
	}
}

void Bullet::update(int id) {
	bool collided = 0;

	if (position.y < 0) {
		deadBullets.push_back(id);
	}

	for (Asteroid& object : asteroids) {
		if (ray::CheckCollisionRecs(ray::Rectangle(position.x - size/2, position.y - size / 2, size, size), ray::Rectangle(object.position.x, object.position.y, object.size.x, object.size.y))) {
			collided = 1;
			object.collided(type);
		}
	}

	if (collided) {
		deadBullets.push_back(id);
	}

	position.y -= speed;

}

void Bullet::draw() {
	ray::DrawTexture(bullet, position.x - size/2 + 1, position.y - size / 2, WHITE);
}


Asteroid asteroidSpawn() {
	Asteroid ast = Asteroid(ray::Vector2(rand() % x, -(rand() % 300)), ray::Vector2(75, 75), rand()%3, 10);
	return ast;
}

void gameStart() {
	damage = 5;
	gameRunning = 1;
	score = 0;
	for (int i = 0; i < 10; i++) asteroids.push_back(asteroidSpawn());
	player.health = 10;
	bullets = {};
	player.position = ray::Vector2(window_size.x / 2 - player.size.x / 2, window_size.y - player.size.y - 10);
}